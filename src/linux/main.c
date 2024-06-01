#include <signal.h>

#include "serial_linux.h"
#include "utils.h"


/*
  serial_linux <serial_file> <baudrate> <file_dump>
*/

#define BUF_SIZE 64
#define USEC_SLEEP 5000
//serial port file descriptor
int fd;


//install signal handler to CTRL+C to close the serial port
void signal_handler(int signum) {
  fprintf(stderr, "Caught signal SIGINT");
  close(fd);
  exit(EXIT_SUCCESS);
}

int main(int argc, const char** argv) {
  int ret;

  signal(SIGINT, signal_handler);

  if (argc < 4) {
    printf("serial_linux <serial_file> <baudrate> <file_dump>\n");
  }
  const char* serial_device = argv[1];
  int baudrate = atoi(argv[2]);
  const char* file_dump = argv[3];

  fd = serial_open(serial_device);
  serial_set_interface_attribs(fd, baudrate, 0);
  serial_set_blocking(fd, 1); //1 se bloccante, 0 altrimenti

  char buffer[BUF_SIZE] = {0};

  if ( (fgets(buffer, BUF_SIZE, stdin) != buffer) ) handle_error("fgets from stdin");
  
  ret = fputs(buffer, stderr);
  if (ret < 0) handle_error("fputs");

  ret = write(fd, buffer, strlen(buffer));
  if (ret < 0) handle_error("write");
  printf("bytes written: %d\n", ret);

  if(buffer[0] == 'Y') {
    printf("ONLINE MODE\n");

    while(1) {
      uint16_t adc_value = 0;
      usleep(USEC_SLEEP); //we wait 5ms per il meme

      ret = read(fd, &adc_value, sizeof(uint16_t));
      if (ret < 0) handle_error("read");
      printf("bytes read: %d\n", ret);
      printf("buffer: %d\n", adc_value);
    } 

  } else {
    printf("QUERY MODE\n");
    while(1) {
    
      //read from stdin any character
      memset(buffer, 0, BUF_SIZE);
      if ( (fgets(buffer, BUF_SIZE, stdin) != buffer) ) handle_error("fgets from stdin");


      Data data = {0};
      ret = write(fd, buffer, sizeof(const char));
      if (ret < 0) handle_error("write");
      fprintf(stderr, "bytes written: %d\n", ret);
      usleep(USEC_SLEEP); //meme
      
      if(buffer[0] == 'Q') {
        ret = read(fd, &data, sizeof(Data));
        printf("bytes read: %d\n", ret);

        if (ret < 0) handle_error("read");

        //TODO check if we read the correct number of bytes
        print_Data(&data);

        dump_Data(&data, file_dump);
      }
    }

  }

  exit(EXIT_SUCCESS);
}
