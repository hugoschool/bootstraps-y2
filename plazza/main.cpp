#include <iostream>
#include <pthread.h>

const int N = 5;

void incrementCounter(int &i)
{
    i += N;
}

struct content {
    int a;
    pthread_mutex_t mutex;
};

void *thread_create(void *ptr)
{
    struct content *content = (struct content *)ptr;

    pthread_mutex_lock(&content->mutex);
    incrementCounter(content->a);
    pthread_mutex_unlock(&content->mutex);
    return NULL;
}

int main(void)
{
    const int T = 5;
    pthread_t threads[T];
    struct content content = {
        .a = 0,
        .mutex = {},
    };

    pthread_mutex_init(&content.mutex, NULL);
    for (unsigned int i = 0; i < T; i++) {
        pthread_create(&(threads[i]), NULL, thread_create, &content);
    }
    for (unsigned int i = 0; i < T; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&content.mutex);

    std::cout << content.a << std::endl;
    return 0;
}
