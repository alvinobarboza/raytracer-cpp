#ifndef RAYTRACER_CPP_THREADPOOL_H
#define RAYTRACER_CPP_THREADPOOL_H
#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

class ThreadPool {
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queueMutex;
    std::condition_variable cv;
    std::condition_variable cv_wait;
    bool stop;
    size_t active_workers;
public:
    explicit ThreadPool(size_t threads);
    ~ThreadPool();

    void wait();
    [[nodiscard]] size_t size() const;

    template<class F>
    void enqueue(F&& f) {
        std::unique_lock lock(queueMutex);
        tasks.emplace(std::forward<F>(f));
        active_workers++;
        lock.unlock();
        cv.notify_one();
    }
};


#endif //RAYTRACER_CPP_THREADPOOL_H
