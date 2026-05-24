#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  while (1) {
    char *buff = NULL;
    size_t size = 0;
    size_t str_size = 0;

    printf("Please enter some text: ");
    str_size = getline(&buff, &size, stdin);
    if (str_size == -1) {
      perror("getline failed");
      exit(EXIT_FAILURE);
    }

    char *tokenized = NULL;
    char *last = buff;
    tokenized = strtok_r(last, " ", &last);
    printf("%s\n", tokenized);
    char *retry = NULL;
    do {
      retry = strtok_r(NULL, " ", &last);
      if (retry != NULL) {
        printf("%s\n", retry);
      }
    } while (retry != NULL);
    free(buff);
  }
  return 0;
}
