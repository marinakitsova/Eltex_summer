#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>

#define MSG_KEY 1234
#define MSG_SIZE 128
#define CLIENT_MSG_TYPE 1
#define SERVER_MSG_TYPE 2

struct msg_buffer {
    long mtype;
    char mtext[MSG_SIZE];
};

int main() {
    int msgid;
    struct msg_buffer msg;

    msgid = msgget(MSG_KEY, IPC_CREAT | 0666);
    if(msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    printf("Сервер: Ожидаем сообщение от клиента...\n");
    msgrcv(msgid, &msg, sizeof(msg.mtext), CLIENT_MSG_TYPE, 0);

    printf("Сервер: Получено сообщение от клиента: %s\n", msg.mtext);

    strcpy(msg.mtext, "hi");
    msg.mtype = SERVER_MSG_TYPE;
    msgsnd(msgid, &msg, sizeof(msg.mtext), 0);

    printf("Сервер: Ответ отправлен клиенту.\n");

    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
