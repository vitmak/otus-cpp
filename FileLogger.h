#pragma once

#include "Logger.h"
#include <fstream>
//--
#include <iostream>
//--

using namespace std::chrono_literals;


class FileLogger : public ILogger {
public:
	FileLogger() = default;
	~FileLogger() override {}

	void Log(const std::shared_ptr<BlockHandler>& blockHandlerPtr) override {
        std::string fileName{ "bulk" + blockHandlerPtr->GetBlockCreatedTime() + ".log"};
        
        std::cout << std::this_thread::get_id() << " " << fileName << " " << blockHandlerPtr->ToString() << std::endl;

        std::ofstream fileCmdBlock;
        fileCmdBlock.open(fileName, std::ios::binary | std::ios::app);

        std::string cmdBlockContent = blockHandlerPtr->ToString();
        fileCmdBlock.write(cmdBlockContent.c_str(), cmdBlockContent.length());
	}
};
