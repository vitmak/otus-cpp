#pragma once

#include "Logger.h"
#include <iostream>
#include <chrono>
#include <thread>


using namespace std::chrono_literals;

class ConsoleLogger : public ILogger {
public:
	ConsoleLogger() = default;
	~ConsoleLogger() override {}

	void Log(std::shared_ptr<BlockHandler>& blockHandlerPtr) override {
		std::this_thread::sleep_for(1000ms);
		std::cout << blockHandlerPtr->ToString() << std::endl;
	}
};
