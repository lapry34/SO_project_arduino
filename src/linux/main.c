#include <signal.h>

#include "serial_linux.h"
#include "utils.h"


/*
  serial_linux <serial_file> <baudrate> <file_dump>
*/

#define BUF_SIZE 512
#define USEC_SLEEP 5000
//serial port file descriptor
int fd;


//install signal handler to CTRL+C to close the serial port
void signal_handler(int signum) {
  if(signum == SIGINT) {
    fprintf(stderr, "Caught signal SIGINT, exiting gracefully...\n");
    close(fd);
    exit(EXIT_SUCCESS);
  }
}

int main(int argc, const char** argv) {
  int ret;

  __sighandler_t sighandler = signal(SIGINT, signal_handler);
  if (sighandler == SIG_ERR) handle_error("signal");

  if (argc < 4) {
    fprintf(stderr, "Invalid Arguments! \n");
    fprintf(stderr, "usage: serial_linux <serial_file> <baudrate> <file_dump>\n");
    exit(EXIT_FAILURE);
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
      uint16_t current_value = 0;
      memset(buffer, 0, BUF_SIZE);
      usleep(USEC_SLEEP); //we wait 5ms per il meme

      ret = read(fd, buffer, sizeof(uint16_t)+sizeof(char));
      if (ret < 0) handle_error("read");

      printf("bytes read: %d\n", ret);
      current_value = *(uint16_t*)buffer;
      printf("current value (mA) : %d\n", current_value);
    } 

  } else {
    printf("QUERY MODE\n");
    while(1) {
    
      //read from stdin any character
      memset(buffer, 0, BUF_SIZE);
      if ( (fgets(buffer, BUF_SIZE, stdin) != buffer) ) handle_error("fgets from stdin"); //fgets returns NULL if error or EOF
      //fgets adds a newline character at the end of the string


      Data data = {0};
      ret = write(fd, buffer, sizeof(const char));
      if (ret < 0) handle_error("write");
      fprintf(stderr, "bytes written: %d\n", ret);
      usleep(USEC_SLEEP); //meme
      
      if(buffer[0] == 'Q') {
        memset(buffer, 0, BUF_SIZE); // puliamo il buffer per sicurezza, anche se lo stiamo sovrascrivendo
        ret = read(fd, &buffer, sizeof(Data)+sizeof(char));
        if (ret < 0) handle_error("read");

        data = *(Data*)buffer;

        //TODO check if we read the correct number of bytes
        if(ret != sizeof(Data)+sizeof(char)) {
          fprintf(stderr, "Error: read %d bytes, expected %lu\n", ret, sizeof(Data)+sizeof(char));
          continue;
        }
        else {
          fprintf(stderr, "Data received correctly\n");
          print_Data(&data);
          dump_Data(&data, file_dump);
        }

      }
    }

  }

  exit(EXIT_SUCCESS);
}
