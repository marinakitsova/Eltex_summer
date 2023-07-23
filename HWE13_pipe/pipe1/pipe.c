#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int fd1[2];
    int fd2[2];
    pid_t pid;


    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
        perror("Ошибка создания канала");
        exit(EXIT_FAILURE);
    }


    pid = fork();

    if (pid < 0) {
        perror("Ошибка создания процесса");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {

        close(fd1[1]);
        close(fd2[0]);

        char buffer[100];

        ssize_t bytesRead1 = read(fd1[0], buffer, sizeof(buffer));
        if (bytesRead1 < 0) {
            perror("Ошибка чтения из первого канала");
            exit(EXIT_FAILURE);
        }

        printf("Дочерний процесс получил из первого канала: %s\n", buffer);

        char message[] = "Привет, родительский процесс!";
        ssize_t bytesWritten2 = write(fd2[1], message, sizeof(message));
        if (bytesWritten2 < 0) {
            perror("Ошибка записи во второй канал");
            exit(EXIT_FAILURE);
        }

        close(fd1[0]);
        close(fd2[1]);
    } else {

        close(fd1[0]);
        close(fd2[1]);

        char message1[] = "Привет, дочерний процесс!";
        ssize_t bytesWritten1 = write(fd1[1], message1, sizeof(message1));
        if (bytesWritten1 < 0) {
            perror("Ошибка записи в первый канал");
            exit(EXIT_FAILURE);
        }

        char buffer[100];

        ssize_t bytesRead2 = read(fd2[0], buffer, sizeof(buffer));
        if (bytesRead2 < 0) {
            perror("Ошибка чтения из второго канала");
            exit(EXIT_FAILURE);
        }

        printf("Родительский процесс получил из второго канала: %s\n", buffer);

        close(fd1[1]);
        close(fd2[0]);
    }

    return 0;
}
