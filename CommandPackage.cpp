#include "CommandPackage.h"


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

        NotifyAll (m_blockHandlerPtr);
    }

    m_blockHandlerPtr = blockHandlerPtr;
}
