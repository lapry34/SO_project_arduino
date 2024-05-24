
#include "serial_linux.h"
#include "utils.h"

/*
  serial_linux <serial_file> <baudrate> 
*/

int main(int argc, const char** argv) {
  int ret;

  if (argc < 3) {
    printf("serial_linux <serial_file> <baudrate> \n");
  }
  const char* serial_device = argv[1];
  int baudrate = atoi(argv[2]);

  int fd = serial_open(serial_device);
  serial_set_interface_attribs(fd, baudrate, 0);
  serial_set_blocking(fd, 1);

  printf("in place\n");
  while(1) {
    
    //read from stdin any character
    getchar();

    Data data = {0};

    const char recv = 'R';

    ret = write(fd, &recv, sizeof(const char));
    if (ret < 0) handle_error("write");

    int nchars = read(fd, &data, sizeof(Data));

    if (nchars < 0) handle_error("read");

    print_Data(&data);


  }

  exit(EXIT_SUCCESS);
}
