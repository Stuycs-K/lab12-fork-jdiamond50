#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
  pid_t p1, p2;
  printf("%d about to create 1 child processes\n", getpid());
  p1 = fork();
  p2 = fork();
  if (p1 < 0 && p2 < 0) {
    perror("fork failed");
  } else if ((p1 != 0 && p2 == 0) || (p1 == 0 && p2 != 0)) {
    int random = open("/dev/random", O_RDONLY);
    int t = 0;
    while (t > 5 || t < 1) {
      read(random, &t, sizeof(int));
      t %= 5;
      t += 1;
    }
    printf("%d %dsec\n", getpid(), t);
    sleep(t);
    printf("%d finished after %dsec\n", getpid(), t);
    exit(t);
  } else if (p1 != 0 && p2 != 0) {
    int status;
    int cpid = wait(&status);
    printf("Main Process %d is done. Child %d slept for %dsec\n", getpid(), cpid, WEXITSTATUS(status));
  }
}
