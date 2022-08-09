#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>


#define NAME "OS"
#define SIZE 4096

int main() {
  int shmFd;
  void *ptr;
  shmFd = shm_open(NAME, O_CREAT | O_RDWR, 0666);
  ftruncate(shmFd, SIZE);
  ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shmFd, 0);
  sprintf(ptr, "%s", "ass");
  return 0;
}
