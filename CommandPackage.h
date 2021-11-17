#pragma once

#include "BlockHandler.h"
#include <iostream>
#include <list>
#include <memory>


class CommandPackage {
public:
    CommandPackage(int blockSize) : m_blockSize{ blockSize } {
        SetBlockHandler (std::make_shared<StandartBlockHandler>());
    }

    void ParseCommand(const Command& cmd);

    void SetBlockHandler(std::shared_ptr<BlockHandler> blockHandlerPtr);

    inline int GetBlockSize() const {
        return m_blockSize;
    }

private:
    void StopBlock() {
        m_blockHandlerPtr->StopBlock(this);
    }

    void StartDymamicBlock() {
        m_blockHandlerPtr->StartDymamicBlock(this);
    }

    void EndDymamicBlock() {
        m_blockHandlerPtr->EndDymamicBlock(this);
    }

    void AddCommandToBlock(const Command& cmd) {
        m_blockHandlerPtr->AddCommandToBlock(this, cmd);
    }

private:
    std::shared_ptr<BlockHandler> m_blockHandlerPtr;
    const int m_blockSize;
    std::list<std::shared_ptr<BlockHandler>> m_cmdPackage;
};
