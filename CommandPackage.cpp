#include "CommandPackage.h"
#include <chrono>
#include <thread>
#include <fstream>

using namespace std::chrono_literals;


void CommandPackage::ParseCommand(const Command& cmd) {
    if (cmd == "EOF") {
        StopBlock();
    }
    else if (cmd == "{") {
        StartDymamicBlock();
    }
    else if (cmd == "}") {
        EndDymamicBlock();
    }
    else {
        AddCommandToBlock(cmd);
    }
}

void CommandPackage::SetBlockHandler(std::shared_ptr<BlockHandler> blockHandlerPtr) {
    if (m_blockHandlerPtr != nullptr && !m_blockHandlerPtr->IsBlockEmpty()) {
        m_cmdPackage.push_back(m_blockHandlerPtr);
    }

    m_blockHandlerPtr = blockHandlerPtr;
}


void CommandPackage::Print(std::ostream& out) const {
    for (const auto v : m_cmdPackage) {
        std::this_thread::sleep_for(1000ms);
        out << v->ToString() << std::endl;
    }
}

void CommandPackage::Save() const {
    std::string fileNamePrefix{ "bulk" };
    std::string fileNamePostfix;

    std::ofstream fileCmdBlock;

    for (const auto v : m_cmdPackage) {
        fileNamePostfix = std::to_string(v->GetCmdBlockCreatedTime());
        fileNamePostfix += ".log";
        fileCmdBlock.open(fileNamePrefix + fileNamePostfix, std::ios::binary | std::ios::app);

        std::string cmdBlockContent = v->ToString();
        fileCmdBlock.write(cmdBlockContent.c_str(), cmdBlockContent.length());

        fileCmdBlock.close();
    }
}
