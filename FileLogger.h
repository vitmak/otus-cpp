#pragma once

#include "Logger.h"
#include <fstream>

using namespace std::chrono_literals;


class FileLogger : public Logger {
public:
	FileLogger() = default;
	~FileLogger() override {}

	void Log(const std::shared_ptr<BlockHandler>& blockHandlerPtr) override {
        std::string fileName{ "bulk" + blockHandlerPtr->GetBlockCreatedTime() + ".log"};
        
        std::ofstream fileCmdBlock;
        fileCmdBlock.open(fileName, std::ios::binary | std::ios::app);

        std::string cmdBlockContent = blockHandlerPtr->ToString();
        fileCmdBlock.write(cmdBlockContent.c_str(), cmdBlockContent.length());
	}
};
