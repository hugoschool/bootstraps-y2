#include <chrono>
#include <condition_variable>
#include <cstdlib>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <iostream>

class ISafeQueue {
    public:
        virtual ~ISafeQueue() = default;
        virtual void push(int value) = 0;
        virtual bool tryPop(int &value) = 0;
        virtual int pop() = 0;
};

template<typename T>
class SafeQueue : public ISafeQueue {
    public:
        SafeQueue() = default;
        ~SafeQueue() = default;

        void push(T value) override
        {
            std::unique_lock lock(_mutex);

            _queue.push(value);
            _cv.notify_all();
        }

        bool tryPop(T &value) override
        {
            std::unique_lock lock(_mutex);

            if (_queue.empty())
                return false;

            value = _queue.front();
            _queue.pop();
            return true;
        }

        T pop() override
        {
            std::unique_lock lock(_mutex);

            _cv.wait(lock, [this]{ return !_queue.empty(); });

            T value = _queue.front();
            _queue.pop();
            return value;
        }

    private:
        std::mutex _mutex;
        std::condition_variable _cv;

        std::queue<T> _queue;
};

using namespace std::chrono_literals;

class Consumer {
    public:
        Consumer() = delete;
        Consumer(std::size_t i, SafeQueue<int> &queue) : _queue(queue)
        {
            _thread = std::thread([this, i]() {
                std::cerr << "Created consumer " << i << std::endl;
                while (true) {
                    int value = _queue.pop();
                    std::cout << "Unstacked value by " << i << ": " << value << std::endl;
                }
            });
        }
        ~Consumer() = default;

        void join()
        {
            _thread.join();
        }

    private:
        SafeQueue<int> &_queue;
        std::thread _thread;
};

class Producer {
    public:
        Producer() = delete;
        Producer(std::size_t i, SafeQueue<int> &queue) : _queue(queue)
        {
            _thread = std::thread([this, i]() {
                std::cerr << "Created producer " << i << std::endl;
                while (true) {
                    _queue.push(std::rand() % 500);
                    std::this_thread::sleep_for(1s);
                }
            });
        }
        ~Producer() = default;

        void join()
        {
            _thread.join();
        }

    private:
        SafeQueue<int> &_queue;
        std::thread _thread;
};

int main(void)
{
    std::srand(std::time(nullptr));

    const std::size_t consumerNb = 2;
    const std::size_t producerNb = 5;
    SafeQueue<int> queue;
    std::unique_ptr<Consumer> consumers[consumerNb];
    std::unique_ptr<Producer> producers[producerNb];

    for (std::size_t i = 0; i < consumerNb; i++)
        consumers[i] = std::make_unique<Consumer>(i, queue);
    for (std::size_t i = 0; i < producerNb; i++)
        producers[i] = std::make_unique<Producer>(i, queue);

    for (std::size_t i = 0; i < consumerNb; i++)
        consumers[i]->join();
    for (std::size_t i = 0; i < producerNb; i++)
        producers[i]->join();
}
