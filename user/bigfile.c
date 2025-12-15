#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int
main()
{
  char buf[512];
  int fd, blocks;
  fd = open("big.file", O_CREATE | O_WRONLY);
  if(fd < 0){
    printf("bigfile: cannot open big.file\n");
    exit(1);
  }
  blocks = 0;
  while(1){
    *(int*)buf = blocks;
    int cc = write(fd, buf, sizeof(buf));
    if(cc <= 0) break;
    blocks++;
    if (blocks % 100 == 0) printf(".");
  }
  printf("\nwrote %d blocks\n", blocks);
  if(blocks > 65803) { printf("bigfile: file is too big\n"); exit(1); }
  if(blocks < 65803) { printf("bigfile: file is too small\n"); exit(1); }
  printf("done; ok\n");
  exit(0);
}