#include <mutex>
#include <shared_mutex>

class ThreadSafeCounter {
private:
    mutable std::shared_mutex mutex_;
    int value_ = 0;

public:
    void increment()
    {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        value_++;
    }

    int get() const
    {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return value_;
    }
};