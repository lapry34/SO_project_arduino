#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>

#include "serial_linux.h"

using namespace std;

/*
  serial_linux <serial_file> <baudrate> <read=1, write=0>
*/

int main(int argc, const char** argv) {
  if (argc < 4) {
    printf("serial_linux <serial_file> <baudrate> <read=1, write=0>\n");
  }
  const char* serial_device=argv[1];
  int baudrate=atoi(argv[2]);
  int read_or_write=atoi(argv[3]);

  int fd=serial_open(serial_device);
  serial_set_interface_attribs(fd, baudrate, 0);
  serial_set_blocking(fd, 1);

  printf("in place\n");
  while(true) {
    char buf[1024];
    memset(buf, 0, 1024);
    if (read_or_write) {
      int nchars=read(fd, buf, 1024);
      printf("%s", buf);
    } else {
      cin.getline(buf, 1024);
      int l=strlen(buf);
      buf[l]='\n';
      ++l;
      write(fd, buf, l);
    }
  }

  exit(EXIT_SUCCESS);
}
