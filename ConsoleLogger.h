#pragma once

#include "Logger.h"
#include <iostream>


class ConsoleLogger : public Logger {
public:
	ConsoleLogger() = default;
	~ConsoleLogger() override = default;

	void Log(const std::shared_ptr<BlockHandler>& blockHandlerPtr) override {
		std::cout << blockHandlerPtr->ToString() << std::endl;
	}
};
