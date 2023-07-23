#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define MAX_MESSAGE_SIZE 256
#define SERVER_QUEUE_NAME "/server_queue"

typedef struct {
    long type;
    char text[MAX_MESSAGE_SIZE];
} Message;

void* receive_messages(void* arg) {
    mqd_t client_queue;
    Message message;


    client_queue = mq_open((char*)arg, O_RDONLY);

    if (client_queue == -1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if (mq_receive(client_queue, (char*)&message, sizeof(Message), NULL) == -1) {
            perror("mq_receive");
            break;
        }

        printf("Received: %s", message.text);

        if (strcmp(message.text, "exit\n") == 0) {
            break;
        }
    }

    mq_close(client_queue);

    return NULL;
}

void* send_messages(void* arg) {
    mqd_t server_queue;
    mqd_t client_queue;
    char buffer[MAX_MESSAGE_SIZE];
    Message message;

    char* client_queue_name = (char*)arg;

    server_queue = mq_open(SERVER_QUEUE_NAME, O_WRONLY);

    if (server_queue == -1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    client_queue = mq_open(client_queue_name, O_RDONLY);

    if (client_queue == -1) {
        perror("mq_open");
        mq_close(server_queue);
        exit(EXIT_FAILURE);
    }

    printf("Enter 'exit' to leave the chat.\n");

    while (1) {
        fgets(buffer, MAX_MESSAGE_SIZE, stdin);

        message.type = 1;
        strncpy(message.text, buffer, MAX_MESSAGE_SIZE);

        if (mq_send(server_queue, (char*)&message, sizeof(Message), 0) == -1) {
            perror("mq_send");
            break;
        }

        if (strcmp(buffer, "exit\n") == 0) {
            break;
        }
    }

    mq_close(server_queue);
    mq_close(client_queue);

    return NULL;
}

int main() {
    pthread_t recv_thread, send_thread;
    char client_queue_name[64];

    printf("Enter your client queue name: ");
    fgets(client_queue_name, sizeof(client_queue_name), stdin);
    client_queue_name[strcspn(client_queue_name, "\n")] = '\0'; 

    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(Message);
    attr.mq_curmsgs = 0;
    mqd_t client_queue = mq_open(client_queue_name, O_CREAT | O_RDONLY, 0644, &attr);

    if (client_queue == -1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    pthread_create(&recv_thread, NULL, receive_messages, (void*)client_queue_name);
    pthread_create(&send_thread, NULL, send_messages, (void*)client_queue_name);

    pthread_join(recv_thread, NULL);
    pthread_join(send_thread, NULL);

    mq_close(client_queue);
    mq_unlink(client_queue_name); 

    return 0;
}
