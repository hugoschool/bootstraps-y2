#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NB_TRAINS 3
#define BRIDGE_START 5
#define BRIDGE_END 10
#define RAILWAY "=====|----|====="
#define RAILWAY_LEN strlen(RAILWAY)
#define USLEEP_SECS 1000

typedef struct {
    size_t i;
} train_t;

typedef struct {
    train_t trains[NB_TRAINS];
} trains_t;

typedef struct {
    trains_t *trains;
    size_t i;
    pthread_mutex_t *mutex;
} train_thread_t;

// #====|----|=====\n
void print_railway_char(size_t i, size_t train_position)
{
    if (i == train_position && (train_position != BRIDGE_START && train_position != BRIDGE_END)) {
        printf("#");
        return;
    }
    if (i <= 4 || i >= 11) {
        printf("=");
        return;
    }
    if (i == BRIDGE_START || i == BRIDGE_END) {
        printf("|");
        return;
    }
    printf("-");
}

bool has_ended(train_t *trains)
{
    for (size_t i = 0; i < NB_TRAINS; i++) {
        if (trains[i].i < RAILWAY_LEN - 1)
            return false;
    }
    return true;
}

void print_trains(trains_t *trains)
{
    do {
        printf("   0123456789012345\n");
        printf("-------------------\n");
        for (size_t train = 0; train < NB_TRAINS; train++) {
            printf("%ld: ", train);
            for (size_t i = 0; i < RAILWAY_LEN; i++) {
                print_railway_char(i, trains->trains[train].i);
            }
            printf("\n");
        }
        usleep(USLEEP_SECS);
    } while (!has_ended(trains->trains));
}

void *train_routine(void *arg)
{
    train_thread_t *thread = arg;

    while (thread->trains->trains[thread->i].i != RAILWAY_LEN - 1) {
        if (thread->trains->trains[thread->i].i == BRIDGE_START - 1) {
            pthread_mutex_lock(thread->mutex);
        }
        thread->trains->trains[thread->i].i += 1;
        if (thread->trains->trains[thread->i].i == BRIDGE_END + 1) {
            pthread_mutex_unlock(thread->mutex);
        }
        usleep(USLEEP_SECS);
    }

    return NULL;
}

int main(void)
{
    trains_t trains = {0};
    pthread_t threads[NB_TRAINS];
    pthread_mutex_t mutex;

    pthread_mutex_init(&mutex, NULL);

    train_thread_t *train = calloc(NB_TRAINS, sizeof(train_thread_t));
    for (int i = 0; i < NB_TRAINS; i++) {
        train[i].trains = &trains;
        train[i].i = i;
        train[i].mutex = &mutex;

        pthread_create(&threads[i], NULL, &train_routine, &train[i]);
    }

    print_trains(&trains);

    for (int i = 0; i < NB_TRAINS; i++) {
        pthread_join(threads[i], NULL);
    }

    free(train);
    pthread_mutex_destroy(&mutex);
    return 0;
}
