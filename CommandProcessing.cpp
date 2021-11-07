﻿#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;


class Command {
public:
    explicit Command(const std::string& cmdName) : m_cmdName(cmdName) {
    }

    bool IsEOF() const {
        return m_cmdName == "EOF";
    }

    bool operator == (const std::string& cmdName) const {
        return m_cmdName == cmdName;
    }

    const std::string& GetName() const {
        return m_cmdName;
    }

private:
    std::string m_cmdName;
};

class CommandPackage;
class BlockHandler {
public:
    virtual void StopBlock(CommandPackage* blockPackagePtr) = 0;
    virtual void StartDymamicBlock(CommandPackage* blockPackagePtr) = 0;
    virtual void EndDymamicBlock(CommandPackage* blockPackagePtr) = 0;
    virtual void AddCommandToBlock(CommandPackage* blockPackagePtr, const Command& cmd) = 0;
    
    //
    virtual bool IsBlockEmpty() const = 0;
    virtual void PrintCommandBlock(std::ostream& out) const = 0;
};

class StandartBlockHandler : public BlockHandler {
public:
    StandartBlockHandler(){}

    void StopBlock(CommandPackage* blockPackagePtr) override;

    void StartDymamicBlock(CommandPackage* blockPackagePtr) override {}

    void EndDymamicBlock(CommandPackage* blockPackagePtr) override {}

    void AddCommandToBlock(CommandPackage* blockPackagePtr, const Command& cmd) override;

    inline bool IsBlockEmpty() const override {
        return m_cmdBlock.empty();
    }

    void PrintCommandBlock(std::ostream& out) const override {
        // Get time
        auto it = m_cmdBlock.cbegin();
        out << "bulk: ";
        out << it->GetName();
        while (++it != m_cmdBlock.cend()) {
            out << ", " << it->GetName();
        }
        out << std::endl;
    }

private:
    std::vector<Command> m_cmdBlock;
};

//class DynamicBlockHanler : public BlockHandler {
//public:
//    DynamicBlockHanler(){}
//
//    void StopBlock(BlockPackage* blockPackagePtr) override  {}
//
//    void StartDymamicBlock(BlockPackage* blockPackagePtr) override  {}
//
//    void EndDymamicBlock(BlockPackage* blockPackagePtr) override {}
//
//    void AddCommandToBlock(BlockPackage* blockPackagePtr, const Command& cmd) override {}
//
//    virtual bool IsBlockEmpty() const override {
//        //return m_cmdBlock.empty();
//        return true;
//    }
//
//private:
//    int m_countOfStartDymamicBlocks = 0;
//};


class CommandPackage {
public:
    CommandPackage(int blockSize) : m_blockSize{blockSize} {
        m_blockHandlerPtr = std::make_shared<StandartBlockHandler>();
    }

    void ParseCommand(const Command& cmd) {
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

    void SetBlockHandler(std::shared_ptr<BlockHandler> blockHandlerPtr) {
        
        if (!m_blockHandlerPtr->IsBlockEmpty())
            m_blockPackage.push_back(m_blockHandlerPtr);
        m_blockHandlerPtr = blockHandlerPtr;
    }

    int GetBlockSize() const {
        return m_blockSize;
    }

    const std::list<std::shared_ptr<BlockHandler>>& GetCommandPackage() const {
        return m_blockPackage;
    }

private:
    void StopBlock(){
        m_blockHandlerPtr->StopBlock(this);
    }

    void StartDymamicBlock() {}

    void EndDymamicBlock() {}

    void AddCommandToBlock(const Command& cmd) {
        m_blockHandlerPtr->AddCommandToBlock(this, cmd);
    }

private:
    std::shared_ptr<BlockHandler> m_blockHandlerPtr;
    const int m_blockSize;
    std::list<std::shared_ptr<BlockHandler>> m_blockPackage;
};


void StandartBlockHandler::AddCommandToBlock(CommandPackage* blockPackagePtr, const Command& cmd) {
    m_cmdBlock.push_back(cmd);
    auto blockSize = blockPackagePtr->GetBlockSize();
    if (m_cmdBlock.size() == blockSize) {
        blockPackagePtr->SetBlockHandler(std::make_shared<StandartBlockHandler>());
    }
}

void StandartBlockHandler::StopBlock(CommandPackage* blockPackagePtr) {
    blockPackagePtr->SetBlockHandler(nullptr);
}


int main(int argc, char* argv[]) {
    std::cout << "There are " << argc << " arguments:\n";

    for (int count = 0; count < argc; ++count)
        std::cout << count << " " << argv[count] << '\n';

    auto val = argv[1];

    CommandPackage commandPackage{ atoi(argv[1]) };

    std::string line;
    while (std::getline(std::cin, line)) {
        
        Command cmd{line};
        commandPackage.ParseCommand(cmd);

        if (cmd.IsEOF())
            break;
    }

    auto cmdBlock = commandPackage.GetCommandPackage();
    for (const auto v : cmdBlock) {
        std::this_thread::sleep_for(1000ms);
        v->PrintCommandBlock(std::cout);
        //v.Save();
    }

    return 0;
}