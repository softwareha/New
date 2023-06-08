#include<errno.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
extern int errno;
int main(){
  int fd = open("foo.txt",O_RDONLY|O_CREAT);
  printf("fd=%d\n",fd);
  if(fd==-1){
   printf("Error Number %D\n",errono);
   perror("Program");
   }
   return 0;
  }
