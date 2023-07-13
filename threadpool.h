#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool {
public:
	ThreadPool(size_t numThreads = -1);
	~ThreadPool();

	template <class F, class... Args>
	void enqueue(F&& f, Args&&... args) {
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_tasks.emplace([=] { f(args...); });
		}

		m_condition.notify_one();
	}

private:
	std::vector<std::thread> m_threads;
	std::queue<std::function<void()>> m_tasks;
	std::mutex m_mutex;
	std::condition_variable m_condition;
	bool m_stop;
};

#endif