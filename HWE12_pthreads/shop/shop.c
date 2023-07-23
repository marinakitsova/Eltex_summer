#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int num_products = 0;
int active_buyers = 5;
int all_buyers_left = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buyer_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t loader_cond = PTHREAD_COND_INITIALIZER;

void *loader_thread(void *arg) {
    while (active_buyers > 0) {
        pthread_mutex_lock(&mutex);
        num_products += 500;
        printf("Товаров в ячейке: %d\n", num_products);
        pthread_cond_broadcast(&buyer_cond);
        pthread_mutex_unlock(&mutex);
        sleep(2);
    }
    all_buyers_left = 1;
    pthread_cond_broadcast(&buyer_cond);
    pthread_exit(NULL);
}

void *buyer_thread(void *arg) {
    int buyer_id = *((int *)arg);
    while (1) {
        pthread_mutex_lock(&mutex);
        while (num_products < 1000 && !all_buyers_left) {
            printf("Покупатель %d ждет товары...\n", buyer_id);
            pthread_cond_wait(&buyer_cond, &mutex);
        }
        if (!all_buyers_left) {
            num_products -= 1000;
            printf("Покупатель %d забрал товары, осталось: %d\n", buyer_id, num_products);
            pthread_mutex_unlock(&mutex);
            sleep(1);
        } else {
            active_buyers--;
            pthread_mutex_unlock(&mutex);
            break;
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t loader_tid;
    pthread_t buyer_tids[5];
    int buyer_ids[5];

    pthread_create(&loader_tid, NULL, loader_thread, NULL);

    for (int i = 0; i < 5; ++i) {
        buyer_ids[i] = i;
        pthread_create(&buyer_tids[i], NULL, buyer_thread, &buyer_ids[i]);
    }

    for (int i = 0; i < 5; ++i) {
        pthread_join(buyer_tids[i], NULL);
    }

    pthread_join(loader_tid, NULL);

    printf("Программа завершена.\n");
    return 0;
}
