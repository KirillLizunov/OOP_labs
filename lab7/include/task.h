#ifndef TASK_H
#define TASK_H

#include <coroutine>

class Task {
public:
    struct promise_type {
        Task get_return_object() {
            return Task{ std::coroutine_handle<promise_type>::from_promise(*this) };
        }
        std::suspend_always initial_suspend() { return {}; }
        auto final_suspend() noexcept {
            return std::suspend_always{};
        }
        void return_void() {}
        void unhandled_exception() {
            std::terminate();
        }
    };

    Task(std::coroutine_handle<promise_type> handle) : coro(handle) {}
    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;

    Task(Task&& other) noexcept : coro(other.coro) { other.coro = nullptr; }
    Task& operator=(Task&& other) noexcept {
        if (this != &other) {
            if (coro) coro.destroy();
            coro = other.coro;
            other.coro = nullptr;
        }
        return *this;
    }

    ~Task() {
        if (coro) coro.destroy();
    }

    void resume() {
        if (coro && !coro.done()) {
            coro.resume();
        }
    }

    bool done() const {
        return !coro || coro.done();
    }

private:
    std::coroutine_handle<promise_type> coro;
};

#endif