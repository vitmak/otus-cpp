#include "BlockHandler.h"
#include "CommandPackage.h"
#include <exception>

using namespace std::chrono_literals;


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

void BlockHandler::PushCommand(const Command& cmd) {
    if (m_cmdBlock.empty()) {
        /*static long cmdID = 0;
        m_timeCmdBlockCreated = std::to_string(std::time(nullptr));
        m_timeCmdBlockCreated += std::to_string(cmdID++);*/
        
        std::this_thread::sleep_for(1ms);
        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
        m_timeCmdBlockCreated = std::to_string(ms.count());
    }

    m_cmdBlock.push_back(cmd);
}


void StandartBlockHandler::StopBlock(CommandPackage* blockPackagePtr) {
    blockPackagePtr->SetBlockHandler(nullptr);
}

void StandartBlockHandler::StartDymamicBlock(CommandPackage* blockPackagePtr) {
    blockPackagePtr->SetBlockHandler(std::make_shared<DynamicBlockHanler>());
}

void StandartBlockHandler::EndDymamicBlock([[maybe_unused]] CommandPackage* blockPackagePtr) {
    throw "Data error: Invalid command structure.";
}

void StandartBlockHandler::AddCommandToBlock(CommandPackage* blockPackagePtr, const Command& cmd) {
    PushCommand(cmd);
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
    PushCommand(cmd);
}
