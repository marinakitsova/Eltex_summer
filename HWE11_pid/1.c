#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void){

    pid_t pid;
    pid_t ppid;

    pid = getpid();
    ppid = getppid();
    printf("child pid = %d, parrent pid = %d\n", pid, ppid);
    return 0;
}
