#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  while (1) {
    char *comm = NULL;
    size_t size = 0;
    size_t str_size = 0;
    int status;
    printf("Enter programs to run.\n");
    str_size = getline(&comm, &size, stdin);
    if (str_size == -1) {
      perror("getline failed");
      exit(EXIT_FAILURE);
    }
    comm[str_size - 1] = '\0';
    str_size = str_size - 1;
    pid_t pid = fork();
    if (pid == -1) {
      perror("Process Failed");
      exit(EXIT_FAILURE);
    } else if (pid == 0) {
      int err = execl(comm, "", NULL);
      if (err == -1) {
        printf("Command Error\n");
      }
    } else {
      pid = waitpid(pid, &status, 0);
      if (status == -1) {
        perror("Proccess failed\n");
        exit(EXIT_FAILURE);
      } else {
        continue;
      }
    }
  }
  return 0;
}
