#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int
main(int argc, char *argv[])
{
  int r, fd1, fd2;
  char buf[32];

  printf("Start: test symlinks\n");

  r = symlink("/testsymlink", "/symlink");
  if(r < 0){
    printf("symlinktest: symlink failed\n");
    exit(1);
  }

  fd1 = open("/symlink", O_CREATE | O_RDWR);
  if(fd1 < 0){
    printf("symlinktest: open symlink failed\n");
    exit(1);
  }
  write(fd1, "hello", 5);
  close(fd1);

  fd2 = open("/testsymlink", O_RDONLY);
  if(fd2 < 0){
    printf("symlinktest: open target failed\n");
    exit(1);
  }
  read(fd2, buf, sizeof(buf));
  if(buf[0] != 'h'){
    printf("symlinktest: read failed\n");
    exit(1);
  }
  close(fd2);

  printf("test symlinks: ok\n");
  exit(0);
}