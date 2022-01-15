//#pragma once

#include "BlockHandler.h"
#include <memory>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <atomic>


class CommandQueue {
public:
	CommandQueue() = default;
	CommandQueue(const CommandQueue&) = delete;

	bool TryPop(std::shared_ptr<BlockHandler>& cmdBlock) {
		std::unique_lock<std::mutex> lock(m_mutex);
		m_cv.wait(lock, [this] { return !m_queue.empty() || m_stopping.load(); });

		if (!m_queue.empty()) {
			cmdBlock = std::move(m_queue.front());
			m_queue.pop();
			
			return true;
		}

		return false;
	}

	void Push(const std::shared_ptr<BlockHandler>& cmdBlock) {
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_queue.push(cmdBlock);
		}
		m_cv.notify_one();
	}

	void NotifyStopping() {
		m_stopping.store(true, std::memory_order_seq_cst);
		m_cv.notify_all();
	}

private:
	std::queue<std::shared_ptr<BlockHandler>> m_queue;
	std::mutex m_mutex;
	std::condition_variable m_cv;
	std::atomic_bool m_stopping = false;
};
