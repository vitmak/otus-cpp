#pragma once

#include <memory>

class BlockHandler;
class ILogger {
public:
	virtual void Log(std::shared_ptr<BlockHandler>& blockHandlerPtr) = 0;
	virtual ~ILogger() {}
};
