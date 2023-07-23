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

int  main() {
    int msgid;
    struct msg_buffer msg;

    msgid = msgget(MSG_KEY, 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    strcpy(msg.mtext, "Hello");
    msg.mtype = CLIENT_MSG_TYPE;
    msgsnd(msgid, &msg, sizeof(msg.mtext), 0);

    printf("Клиент: Отправлено сообщение серверу: %s\n", msg.mtext);

    msgrcv(msgid, &msg, sizeof(msg.mtext), SERVER_MSG_TYPE, 0);

    printf("Клиент: Получен ответ от сервера: %s\n", msg.mtext);

    return 0;
}
