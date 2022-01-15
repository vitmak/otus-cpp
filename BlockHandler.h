#pragma once

#include "Command.h"
#include <string>
#include <list>
#include <ctime>


class CommandPackage;
class BlockHandler {
public:
    virtual void StopBlock(CommandPackage* blockPackagePtr) = 0;
    virtual void StartDymamicBlock(CommandPackage* blockPackagePtr) = 0;
    virtual void EndDymamicBlock(CommandPackage* blockPackagePtr) = 0;
    virtual void AddCommandToBlock(CommandPackage* blockPackagePtr, const Command& cmd) = 0;

public:
    BlockHandler() = default;

    inline bool IsBlockEmpty() const {
        return m_cmdBlock.empty();
    }

    std::string ToString() const;
    inline std::string GetBlockCreatedTime() const {
        return m_timeCmdBlockCreated;
    }

    void PushCommand(const Command& cmd);

protected:
    std::list<Command> m_cmdBlock;
    std::string        m_timeCmdBlockCreated;
};


class StandartBlockHandler : public BlockHandler {
public:
    StandartBlockHandler() = default;

    void StopBlock(CommandPackage* blockPackagePtr) override;

    void StartDymamicBlock(CommandPackage* blockPackagePtr) override;

    void EndDymamicBlock(CommandPackage* blockPackagePtr) override;

    void AddCommandToBlock(CommandPackage* blockPackagePtr, const Command& cmd) override;
};


class DynamicBlockHanler : public BlockHandler {
public:
    DynamicBlockHanler() : m_countOfStartDymamicBlocks{ 1 } {}

    void StopBlock(CommandPackage* blockPackagePtr) override;

    inline void StartDymamicBlock(CommandPackage* blockPackagePtr) override {
        (void*)blockPackagePtr;
        ++m_countOfStartDymamicBlocks;
    }

    void EndDymamicBlock(CommandPackage* blockPackagePtr) override;

    void AddCommandToBlock(CommandPackage* blockPackagePtr, const Command& cmd) override;

private:
    int m_countOfStartDymamicBlocks;
};