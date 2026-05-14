#include <mutex>
#include <queue>


class ISafeQueue {
    public:
        virtual ~ISafeQueue() = default;
        virtual void push(int value) = 0;
        virtual bool tryPop(int &value) = 0;
};

class SafeQueue : public ISafeQueue {
    public:
        SafeQueue() = default;
        ~SafeQueue() = default;

        void push(int value) override
        {
            std::unique_lock lock(_mutex);

            _queue.push(value);
        }

        bool tryPop(int &value) override
        {
            std::unique_lock lock(_mutex);

            if (_queue.empty())
                return false;

            value = _queue.front();
            _queue.pop();
            return true;
        }

    private:
        std::mutex _mutex;

        std::queue<int> _queue;
};
