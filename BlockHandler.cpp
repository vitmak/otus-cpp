#include "BlockHandler.h"
#include "CommandPackage.h"
#include <exception>

#include <chrono>
#include <thread>
#include <fstream>

using namespace std::chrono_literals;


BlockHandler::BlockHandler() {
    m_timeCmdBlockCreated = std::time(nullptr);
}

std::string BlockHandler::ToString() const {
    if (m_cmdBlock.empty())
        return "";

    std::string buf{ "bulk: " };
    auto it = m_cmdBlock.cbegin();

    buf += it->GetName();
    while (++it != m_cmdBlock.cend()) {
        buf += ", ";
        buf += it->GetName();
    }
    return buf;
}

void BlockHandler::Print(std::ostream& out) const {
    std::this_thread::sleep_for(1000ms);
    out << ToString() << std::endl;
}

void BlockHandler::Save() const {
    std::string fileNamePrefix{ "bulk" };
    std::string fileNamePostfix;

    std::ofstream fileCmdBlock;

    fileNamePostfix = std::to_string(m_timeCmdBlockCreated);
    fileNamePostfix += ".log";
    fileCmdBlock.open(fileNamePrefix + fileNamePostfix, std::ios::binary | std::ios::app);

    std::string cmdBlockContent = ToString();
    fileCmdBlock.write(cmdBlockContent.c_str(), cmdBlockContent.length());

    fileCmdBlock.close();
}

void BlockHandler::Logging() const {
    Print(std::cout);
    Save();
}


void StandartBlockHandler::StopBlock(CommandPackage* blockPackagePtr) {
    blockPackagePtr->SetBlockHandler(nullptr);
}

void StandartBlockHandler::StartDymamicBlock(CommandPackage* blockPackagePtr) {
    blockPackagePtr->SetBlockHandler(std::make_shared<DynamicBlockHanler>());
}

void StandartBlockHandler::EndDymamicBlock([[maybe_unused]] CommandPackage* blockPackagePtr) {
    //(void*)blockPackagePtr;
    throw "Data error: Invalid command structure.";
}

void StandartBlockHandler::AddCommandToBlock(CommandPackage* blockPackagePtr, const Command& cmd) {
    m_cmdBlock.push_back(cmd);
    auto blockSize = blockPackagePtr->GetBlockSize();
    if (m_cmdBlock.size() == blockSize) {
        blockPackagePtr->SetBlockHandler(std::make_shared<StandartBlockHandler>());
    }
}

void DynamicBlockHanler::StopBlock(CommandPackage* blockPackagePtr) {
    m_cmdBlock.clear();
    blockPackagePtr->SetBlockHandler(nullptr);
}

void DynamicBlockHanler::EndDymamicBlock(CommandPackage* blockPackagePtr) {
    --m_countOfStartDymamicBlocks;
    if (m_countOfStartDymamicBlocks == 0) {
        blockPackagePtr->SetBlockHandler(std::make_shared<StandartBlockHandler>());
    }
}

void DynamicBlockHanler::AddCommandToBlock([[maybe_unused]] CommandPackage* blockPackagePtr, const Command& cmd) {
    m_cmdBlock.push_back(cmd);
}
