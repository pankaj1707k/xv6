#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

int
main()
{
  char buf[BSIZE];
  int fd, i, blocks;

  fd = open("big.file", O_CREATE | O_WRONLY);
  if(fd < 0){
    printf(1,"bigfile: cannot open big.file for writing\n");
    exit();
  }

  blocks = 0;
  while(1){
    *(int*)buf = blocks;
    int cc = write(fd, buf, sizeof(buf));
    if(cc <= 0)
      break;
    blocks++;
    if (blocks % 100 == 0)
      printf(1,".");
  }

  printf(1,"\nwrote %d blocks\n", blocks);
  if(blocks != 65803) {
    printf(1,"bigfile: file is too small\n");
    exit();
  }
  
  close(fd);
  fd = open("big.file", O_RDONLY);
  if(fd < 0){
    printf(1,"bigfile: cannot re-open big.file for reading\n");
    exit();
  }
  for(i = 0; i < blocks; i++){
    int cc = read(fd, buf, sizeof(buf));
    if(cc <= 0){
      printf(1,"bigfile: read error at block %d\n", i);
      exit();
    }
    if(*(int*)buf != i){
      printf(1,"bigfile: read the wrong data (%d) for block %d\n",
             *(int*)buf, i);
      exit();
    }
  }

  printf(1,"bigfile done; ok\n"); 

  exit();
}