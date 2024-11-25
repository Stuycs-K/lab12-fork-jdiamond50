#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
  int random = open("/dev/random", O_RDONLY);
  pid_t p;
  printf("%d about to create 1 child processes", getpid());
  p = fork();
  if (p < 0) {
    perror("fork failed");
  } else if (p == 0) {
    int t = 0;
    while (t > 5 || t < 1) {
      read(random, &t, sizeof(int));
    }
    sleep(t);
    exit(0);
    printf("%d %dsec", getpid(), t);
  }
  wait(NULL);
}
