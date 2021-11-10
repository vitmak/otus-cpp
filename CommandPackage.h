#pragma once

#include "BlockHandler.h"
#include <iostream>
#include <map>
#include <ctime>


class CommandPackage {
public:
    CommandPackage(int blockSize) : m_blockSize{ blockSize } {
        m_blockHandlerPtr = std::make_shared<StandartBlockHandler>();
    }

    void ParseCommand(const Command& cmd);

    void SetBlockHandler(std::shared_ptr<BlockHandler> blockHandlerPtr);

    inline int GetBlockSize() const {
        return m_blockSize;
    }

    void Print(std::ostream& out) const;

    void Save() const;

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
    std::map<std::shared_ptr<BlockHandler>, std::time_t> m_cmdPackage;
};
