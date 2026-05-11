#include <iostream>
#include <memory>
#include <pthread.h>

class IMutex {
    public:
        virtual ~IMutex() = default;
        virtual void lock() = 0;
        virtual void unlock() = 0;
        virtual void trylock() = 0;
};

class Mutex : public IMutex {
    public:
        Mutex() : _mutex()
        {
            pthread_mutex_init(&_mutex, NULL);
        };

        ~Mutex()
        {
            pthread_mutex_destroy(&_mutex);
        }

        void lock() override
        {
            pthread_mutex_lock(&_mutex);
        }

        void unlock() override
        {
            pthread_mutex_unlock(&_mutex);
        }

        void trylock() override
        {
            int a = pthread_mutex_trylock(&_mutex);
            static_cast<void>(a);
        }

    private:
        pthread_mutex_t _mutex;
};

class ScopedLock {
    public:
        ScopedLock() = delete;
        ScopedLock(IMutex &mutex) : _mutex(mutex)
        {
            _mutex.lock();
        }
        ~ScopedLock()
        {
            _mutex.unlock();
        }

    private:
        IMutex &_mutex;
};

const int N = 5;

void incrementCounter(int &i)
{
    i += N;
}

struct content {
    int a;
    std::unique_ptr<IMutex> mutex;
};

void *thread_create(void *ptr)
{
    struct content *content = (struct content *)ptr;
    ScopedLock lock(*content->mutex);

    incrementCounter(content->a);
    return NULL;
}

int main(void)
{
    const int T = 5;
    pthread_t threads[T];
    struct content content = {
        .a = 0,
        .mutex = std::make_unique<Mutex>(),
    };

    for (unsigned int i = 0; i < T; i++) {
        pthread_create(&(threads[i]), NULL, thread_create, &content);
    }
    for (unsigned int i = 0; i < T; i++) {
        pthread_join(threads[i], NULL);
    }

    std::cout << content.a << std::endl;
    return 0;
}
