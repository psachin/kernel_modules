/* user application which reads and writes to a device */
/* 
   Usage:
   % make
   % ./userapp
 */
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

#define DEVICE "/dev/testCharDevice"

int main(int argc, char *argv[])
{
  int i, fd;
  char ch, write_buf[100], read_buf[100];

  fd = open(DEVICE, O_RDWR);	/* open for read/write */

  if(fd == -1){
    printf("file %s either doesnot exit, or locked by another process\n", DEVICE);
    exit(-1);
  }
  printf("r - read from device,\nw- write from device\nEnter command: ");
  scanf("%c", &ch);

  switch (ch){
  case 'w':
    printf ("enter data: ");
    scanf("%s", write_buf);
    write(fd, write_buf, sizeof(write_buf));
    break;

  case 'r':
    read(fd, read_buf, sizeof(read_buf));
    printf ("device: %s\n", read_buf);
    break;

  default:
    printf ("command not recognized\n");
    break;
  }

  close(fd);
  return 0;
}

