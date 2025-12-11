#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

const char *separators = " -\r\t\n./,";

int
is_separator(char c)
{
  return strchr(separators, c) != 0;
}

void
sixfive(int fd)
{
  char c;
  char buf[32]; 
  int idx = 0;  
  int valid_start = 1; 

  while(read(fd, &c, 1) > 0){
    if(c >= '0' && c <= '9'){

      if(idx < sizeof(buf) - 1){
        buf[idx++] = c;
      }
    } else if(is_separator(c)){
 
      if(idx > 0 && valid_start){
      
        buf[idx] = 0;
        int n = atoi(buf);
        if(n % 5 == 0 || n % 6 == 0){
          printf("%d\n", n);
        }
      }
      idx = 0;
      valid_start = 1; 
    } else {
      idx = 0;
      valid_start = 0;
    }
  }

  if(idx > 0 && valid_start){
    buf[idx] = 0;
    int n = atoi(buf);
    if(n % 5 == 0 || n % 6 == 0){
      printf("%d\n", n);
    }
  }
}

int
main(int argc, char *argv[])
{
  int i, fd;

  if(argc <= 1){
    sixfive(0); 
    exit(0);
  }

  for(i = 1; i < argc; i++){
    if((fd = open(argv[i], O_RDONLY)) < 0){
      fprintf(2, "sixfive: cannot open %s\n", argv[i]);
      exit(1);
    }
    sixfive(fd);
    close(fd);
  }
  exit(0);
}