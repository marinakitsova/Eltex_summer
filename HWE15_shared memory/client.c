#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_MESSAGE_SIZE 1024
#define SERVER_QUEUE_KEY 1234
#define MAX_CLIENTS 10

typedef struct {
    long type;
    char text[MAX_MESSAGE_SIZE];
} Message;

void* receive_messages(void* arg) {
    int server_queue_id = *((int*)arg);
    Message message;

    while (1) {
        if (msgrcv(server_queue_id, &message, sizeof(Message) - sizeof(long), 0, 0) == -1) {
            perror("msgrcv");
            break;
        }

        printf("Received: %s", message.text);

        if (strcmp(message.text, "exit\n") == 0) {
            break;
        }
    }

    return NULL;
}

void* send_messages(void* arg) {
    int server_queue_id;
    int client_queue_id;
    char buffer[MAX_MESSAGE_SIZE];
    Message message;

    char* client_queue_name = (char*)arg;

    client_queue_id = msgget(ftok(client_queue_name, 1), IPC_CREAT | 0666);

    if (client_queue_id == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    server_queue_id = msgget(SERVER_QUEUE_KEY, 0);

    if (server_queue_id == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    printf("Введите 'exit' для выхода из чата.\n");

    while (1) {
        fgets(buffer, MAX_MESSAGE_SIZE, stdin);

        message.type = 1;
        strncpy(message.text, buffer, MAX_MESSAGE_SIZE);

        if (msgsnd(client_queue_id, &message, sizeof(Message) - sizeof(long), 0) == -1) {
            perror("msgsnd");
            break;
        }

        if (strcmp(buffer, "exit\n") == 0) {
            break;
        }
    }

    return NULL;
}

int main() {
    pthread_t recv_thread, send_thread;
    char client_queue_name[64];

    printf("Введите имя вашей клиентской очереди: ");
    fgets(client_queue_name, sizeof(client_queue_name), stdin);
    client_queue_name[strcspn(client_queue_name, "\n")] = '\0'; 

    int client_queue_id = msgget(ftok(client_queue_name, 1), IPC_CREAT | 0666);

    if (client_queue_id == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    pthread_create(&recv_thread, NULL, receive_messages, (void*)&client_queue_id);
    pthread_create(&send_thread, NULL, send_messages, (void*)client_queue_name);

    pthread_join(recv_thread, NULL);
    pthread_join(send_thread, NULL);

    return 0;
}
