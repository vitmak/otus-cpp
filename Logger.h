#pragma once

#include "CommandQueue.h"
#include <memory>


class BlockHandler;
class ILogger {
public:
	virtual ~ILogger() = default;

	void Logging() {
		std::shared_ptr<BlockHandler> blockHandler;
		while (m_queue.TryPop(blockHandler)) {
			Log(blockHandler);
		}
	}

public:
	CommandQueue m_queue;

protected:
	virtual void Log(const std::shared_ptr<BlockHandler>& blockHandler) = 0;
};
