#pragma once

#include "Logger.h"
#include <fstream>

using namespace std::chrono_literals;

class FileLogger : public ILogger {
public:
	FileLogger() = default;
	~FileLogger() override {}

	void Log(std::shared_ptr<BlockHandler>& blockHandlerPtr) override {
        std::string fileNamePrefix{ "bulk" };
        std::string fileNamePostfix;

        std::ofstream fileCmdBlock;

        fileNamePostfix = std::to_string(blockHandlerPtr->GetBlockCreatedTime());
        fileNamePostfix += ".log";
        fileCmdBlock.open(fileNamePrefix + fileNamePostfix, std::ios::binary | std::ios::app);

        std::string cmdBlockContent = blockHandlerPtr->ToString();
        fileCmdBlock.write(cmdBlockContent.c_str(), cmdBlockContent.length());

        fileCmdBlock.close();
	}
};
