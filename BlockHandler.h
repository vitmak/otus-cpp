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
    BlockHandler();

    inline bool IsBlockEmpty() const {
        return m_cmdBlock.empty();
    }

    std::string ToString() const;

    std::time_t GetCmdBlockCreatedTime() const {
        return m_timeCmdBlockCreated;
    }

protected:
    std::list<Command> m_cmdBlock;
    std::time_t        m_timeCmdBlockCreated = 0;
};


class StandartBlockHandler : public BlockHandler {
public:
    StandartBlockHandler() = default;

    void StopBlock(CommandPackage* blockPackagePtr) override;

    void StartDymamicBlock(CommandPackage* blockPackagePtr) override;

    void EndDymamicBlock([[maybe_unused]] CommandPackage* blockPackagePtr) override;

    void AddCommandToBlock(CommandPackage* blockPackagePtr, const Command& cmd) override;
};


class DynamicBlockHanler : public BlockHandler {
public:
    DynamicBlockHanler() : m_countOfStartDymamicBlocks{ 1 } {}

    void StopBlock(CommandPackage* blockPackagePtr) override;

    inline void StartDymamicBlock([[maybe_unused]] CommandPackage* blockPackagePtr) override {
        ++m_countOfStartDymamicBlocks;
    }

    void EndDymamicBlock(CommandPackage* blockPackagePtr) override;

    void AddCommandToBlock(CommandPackage* blockPackagePtr, const Command& cmd) override;

private:
    int m_countOfStartDymamicBlocks;
};