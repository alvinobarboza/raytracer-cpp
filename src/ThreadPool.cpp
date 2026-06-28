#include "ThreadPool.h"

ThreadPool::ThreadPool(const size_t threads): stop(false), active_workers(0) {
    for (size_t i = 0; i < threads; i++) {
        workers.emplace_back([this] {
            for (;;) {
                std::unique_lock lock(queueMutex);

                cv.wait(lock, [this] {
                    return stop || !tasks.empty();
                });

                if (stop && tasks.empty())
                    return;

                auto task = std::move(tasks.front());
                tasks.pop();
                lock.unlock();

                task();

                lock.lock();
                active_workers--;
                if (active_workers == 0) {
                    cv_wait.notify_all();
                }
            }
        });
    }
}

void ThreadPool::wait() {
    std::unique_lock lock(queueMutex);
    cv_wait.wait(lock, [this] {
        return active_workers == 0;
    });
}

ThreadPool::~ThreadPool() {
    std::unique_lock lock(queueMutex);
    stop = true;
    lock.unlock();
    cv.notify_all();

    for (std::thread &worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

size_t ThreadPool::size() const {
    return workers.size();
}