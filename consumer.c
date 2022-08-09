#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>


#define NAME "OS"
#define SIZE 4096

int main() {
  int shmFd;
  void *ptr;
  shmFd = shm_open(NAME, O_RDONLY, 0666);
  ftruncate(shmFd, SIZE);
  ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shmFd, 0);
  printf("%s\n", (char*)ptr);
  shm_unlink(NAME);
  return 0;
}

