
#include "serial_linux.h"
#include "utils.h"

/*
  serial_linux <serial_file> <baudrate> 
*/

int main(int argc, const char** argv) {
  int ret;

  if (argc < 4) {
    printf("serial_linux <serial_file> <baudrate> <file_dump> \n");
  }
  const char* serial_device = argv[1];
  int baudrate = atoi(argv[2]);
  const char* file_dump = argv[3];

  int fd = serial_open(serial_device);
  serial_set_interface_attribs(fd, baudrate, 0);
  serial_set_blocking(fd, 1); //1 se bloccante, 0 altrimenti

  printf("in place\n");
  while(1) {
    
    //read from stdin any character
    getchar();

    Data data = {0};

    const char recv = 'R';

    ret = write(fd, &recv, sizeof(const char));
    if (ret < 0) handle_error("write");
    fprintf(stderr, "ret: %d\n", ret);
    
    //pragma atomic force on, mettere sleep cose varie per vedere se funziona, cit prof.
    
    int nchars = read(fd, &data, sizeof(Data));
    fprintf(stderr, "nchars: %d\n", nchars);

    if (nchars < 0) handle_error("read");

    print_Data(&data);

    dump_Data(&data, file_dump);


  }

  exit(EXIT_SUCCESS);
}
