#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void create_pyramid(int level, int max_levels) {
    if(level >= max_levels) {
        return;
    }

    int i;
    for(i = 0; i < level + 2; i++) {
        pid_t pid = fork();

        if(pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            printf("Child: PID=%d\nPPID=%d\n\n", getpid(), getppid());
            create_pyramid(level + 1, max_levels);
            exit(EXIT_SUCCESS);
        } else {
            wait(NULL);
        }
    }
}

int main() {
    printf("Parent: PID=%d\n", getpid());
    create_pyramid(0, 3);

    return 0;
}
