#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_FILE1 "/tmp/myfifo1" 
#define FIFO_FILE2 "/tmp/myfifo2" 

int main() {
    pid_t pid; 


    if (mkfifo(FIFO_FILE1, 0666) == -1) {
        perror("Ошибка создания первого именованного канала");
        exit(EXIT_FAILURE);
    }

    if (mkfifo(FIFO_FILE2, 0666) == -1) {
        perror("Ошибка создания второго именованного канала");
        unlink(FIFO_FILE1); 
        exit(EXIT_FAILURE);
    }


    pid = fork();

    if (pid < 0) {
        perror("Ошибка создания процесса");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {



        int fd_read = open(FIFO_FILE1, O_RDONLY);
        int fd_write = open(FIFO_FILE2, O_WRONLY);

        if (fd_read == -1 || fd_write == -1) {
            perror("Ошибка открытия именованных каналов");
            exit(EXIT_FAILURE);
        }


        char buffer[100];


        ssize_t bytesRead = read(fd_read, buffer, sizeof(buffer));
        if (bytesRead < 0) {
            perror("Ошибка чтения из первого канала");
            exit(EXIT_FAILURE);
        }


        printf("Дочерний процесс получил из первого канала: %s\n", buffer);

 
        char message[] = "Привет, родительский процесс!";
        ssize_t bytesWritten = write(fd_write, message, sizeof(message));
        if (bytesWritten < 0) {
            perror("Ошибка записи во второй канал");
            exit(EXIT_FAILURE);
        }


        close(fd_read);
        close(fd_write);
        unlink(FIFO_FILE1);
        unlink(FIFO_FILE2);
    } else {

        int fd_read = open(FIFO_FILE2, O_RDONLY);
        int fd_write = open(FIFO_FILE1, O_WRONLY);

        if (fd_read == -1 || fd_write == -1) {
            perror("Ошибка открытия именованных каналов");
            exit(EXIT_FAILURE);
        }


        char message1[] = "Привет, дочерний процесс!";
        ssize_t bytesWritten = write(fd_write, message1, sizeof(message1));
        if (bytesWritten < 0) {
            perror("Ошибка записи в первый канал");
            exit(EXIT_FAILURE);
        }


        char buffer[100];


        ssize_t bytesRead = read(fd_read, buffer, sizeof(buffer));
        if (bytesRead < 0) {
            perror("Ошибка чтения из второго канала");
            exit(EXIT_FAILURE);
        }


        printf("Родительский процесс получил из второго канала: %s\n", buffer);


        close(fd_read);
        close(fd_write);
        unlink(FIFO_FILE1);
        unlink(FIFO_FILE2);
    }

    return 0;
}
