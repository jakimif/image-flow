#include "threadpool.h"

ThreadPool::ThreadPool(size_t numThreads) : m_stop(false) {
	if (numThreads == -1) {
		numThreads = std::thread::hardware_concurrency();
	}

	for (size_t i = 0; i < numThreads; ++i) {
		m_threads.emplace_back([this] {
			while (true) {
				std::function<void()> task;
				{
					std::unique_lock<std::mutex> lock(m_mutex);
					m_condition.wait(lock, [this] { return m_stop || !m_tasks.empty(); });

					if (m_stop && m_tasks.empty()) {
						return;
					}

					task = std::move(m_tasks.front());
					m_tasks.pop();
				}

				task();
			}
		});
	}
}

ThreadPool::~ThreadPool() {
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_stop = true;
	}

	m_condition.notify_all();

	for (std::thread& thread : m_threads) {
		thread.join();
	}
}