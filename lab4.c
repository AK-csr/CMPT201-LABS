#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int BUF_SIZE = 64;

struct header {
  uint64_t size;
  struct header *next;
};

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);
  if (len < 0) {
    perror("snprint");
  }
  write(STDOUT_FILENO, buf, len);
}

void printHeader(struct header *header) {
  printf("Block Address: %p\n", sizeof(header));
  printf("Size: %ld\n", header->size);
  printf("Next Ptr: %p\n", header->next);
}

void printBlock(char *start) {
  for (int i = 0; i < (128 - sizeof(struct header)); i++) {
    char *addr = (start + sizeof(struct header) + i);
    uint64_t val = (uint64_t)*addr;
    print_out("%lu\n", &val, sizeof(val));
  }
}

void initializeHeader(struct header *header, int num) {
  memset(header + 1, num, 128 - sizeof(struct header));
}

int main(void) {
  char *progBrk = sbrk(256);
  if (progBrk == (void *)-1) {
    perror("sbrk failed");
    exit(EXIT_FAILURE);
  }

  struct header *block1 = (struct header *)progBrk;
  block1->size = 128;
  block1->next = NULL;
  initializeHeader(block1, 0);
  print_out("First Block: %p\n", &block1, sizeof(block1));

  struct header *block2 = (struct header *)(progBrk + 128);
  block2->size = 128;
  block2->next = block1;
  initializeHeader(block2, 1);
  print_out("Second block: %p\n\n", &block2, sizeof(block2));

  print_out("First block size: %ld\n", &block1->size, sizeof(block1->size));
  print_out("First block next: %p\n", &block1->next, sizeof(block1->next));
  print_out("Second block size: %ld\n", &block2->size, sizeof(block2->size));
  print_out("Second block next: %p\n", &block2->next, sizeof(block2->next));

  printBlock((char *)block1);
  printBlock((char *)block2);

  return 0;
}
