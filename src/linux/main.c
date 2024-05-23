
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "serial_linux.h"

/*
  serial_linux <serial_file> <baudrate> <read=1, write=0>
*/

#define BUF_SIZE 1024

int main(int argc, const char** argv) {
  int ret;

  if (argc < 4) {
    printf("serial_linux <serial_file> <baudrate> <read=1, write=0>\n");
  }
  const char* serial_device = argv[1];
  int baudrate = atoi(argv[2]);
  int read_or_write = atoi(argv[3]);

  int fd = serial_open(serial_device);
  serial_set_interface_attribs(fd, baudrate, 0);
  serial_set_blocking(fd, 1);

  printf("in place\n");
  while(1) {
    char buf[BUF_SIZE] = {0};

    if (read_or_write) {
      int nchars = read(fd, buf,BUF_SIZE);

      if (nchars < 0) handle_error("read");

      printf("%s", buf);
    } else {
      char* ret_ptr = fgets(buf, BUF_SIZE, stdin);
      if (ret_ptr == NULL) handle_error("fgets");

      int l = strlen(buf);
      buf[l++]='\n';

      ret = write(fd, buf, l);
      if (ret < 0) handle_error("write");
    }
  }

  exit(EXIT_SUCCESS);
}
