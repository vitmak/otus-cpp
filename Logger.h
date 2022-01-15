#pragma once

#include "CommandQueue.h"
#include <memory>

#include <iostream>

class BlockHandler;
class ILogger {
public:
	virtual ~ILogger() = default;

	void Logging() {
		std::cout << "Thread " << std::this_thread::get_id() << " stared..." << std::endl;
		std::shared_ptr<BlockHandler> blockHandler;
		while (m_queue.TryPop(blockHandler)) {
			Log(blockHandler);
		}

		std::cout << "Thread " << std::this_thread::get_id() << " finished..." << std::endl;
	}

public:
	CommandQueue m_queue;

protected:
	virtual void Log(const std::shared_ptr<BlockHandler>& blockHandler) = 0;
};
