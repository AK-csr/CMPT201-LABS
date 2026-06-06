#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define MAX_LEN 5

char *input[MAX_LEN];

void printAll(int *pos) {
  for (int i = 0; i < *pos; i++) {
    printf("%s\n", input[i]);
  }
}

void add_str(char *buff, int *pos) {
  input[*pos] = buff;
  *pos = (*pos) + 1;
}

void remove_last(char *buff, int *pos) {
  if (*pos > 0) {
    free(input[0]);
    for (int i = 1; i < *pos; i++) {
      input[i - 1] = input[i];
    }
    *pos = (*pos) - 1;
    add_str(buff, pos);
  }
}
int main() {
  int pos = 0;
  while (1) {

    char *buff = NULL;
    char size = 0;

    printf("ENTER STRING: ");
    ssize_t num_char = getline(&buff, &size, stdin);
    if (num_char == -1) {
      perror("Invalid String\n");
      exit(EXIT_FAILURE);
    }
    if (num_char > 0 && buff[num_char - 1] == '\n') {
      buff[num_char - 1] = '\0';
    }
    if (strcmp(buff, "print") == 0) {
      add_str(buff, &pos);
      printAll(&pos);
    } else if (pos == MAX_LEN) {
      remove_last(buff, &pos);
    } else {

      add_str(buff, &pos);
    }
  }
  return 0;
}
