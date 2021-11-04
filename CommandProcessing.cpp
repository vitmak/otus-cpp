#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <cstdlib>


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

class BlockPackage;
class BlockHandler {
public:
    virtual void StopBlock(BlockPackage* blockPackagePtr) = 0;
    virtual void StartDymamicBlock(BlockPackage* blockPackagePtr) = 0;
    virtual void EndDymamicBlock(BlockPackage* blockPackagePtr) = 0;
    virtual void AddCommandToBlock(BlockPackage* blockPackagePtr, const Command& cmd) = 0;
    
    //
    virtual bool IsBlockEmpty() const = 0;
    virtual void PrintCommandBlock(std::ostream& out) const = 0;
};

class StandartBlockHandler : public BlockHandler {
public:
    StandartBlockHandler(){}

    void StopBlock(BlockPackage* blockPackagePtr) override;

    void StartDymamicBlock(BlockPackage* blockPackagePtr) override {}

    void EndDymamicBlock(BlockPackage* blockPackagePtr) override {}

    void AddCommandToBlock(BlockPackage* blockPackagePtr, const Command& cmd) override;

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


class BlockPackage {
public:
    BlockPackage(int blockSize) : m_blockSize{blockSize} {
        m_blockHandlerPtr = new StandartBlockHandler{};
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

    void SetBlockHandler(BlockHandler* blockHandlerPtr) {
        
        if (!m_blockHandlerPtr->IsBlockEmpty())
            m_blockPackage.push_back(m_blockHandlerPtr);
        m_blockHandlerPtr = blockHandlerPtr;
    }

    int GetBlockSize() const {
        return m_blockSize;
    }

    const std::list<BlockHandler*>& GetCommandPackage() const {
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
    BlockHandler* m_blockHandlerPtr;
    const int m_blockSize;
    std::list<BlockHandler*> m_blockPackage;
};


void StandartBlockHandler::AddCommandToBlock(BlockPackage* blockPackagePtr, const Command& cmd) {
    m_cmdBlock.push_back(cmd);
    auto blockSize = blockPackagePtr->GetBlockSize();
    if (m_cmdBlock.size() == blockSize) {
        blockPackagePtr->SetBlockHandler(new StandartBlockHandler{});
    }
}

void StandartBlockHandler::StopBlock(BlockPackage* blockPackagePtr) {
    blockPackagePtr->SetBlockHandler(nullptr);
}


int main(int argc, char* argv[]) {
    std::cout << "There are " << argc << " arguments:\n";

    for (int count = 0; count < argc; ++count)
        std::cout << count << " " << argv[count] << '\n';

    auto val = argv[1];

    BlockPackage blockPackage{ atoi(argv[1]) };

    std::string line;
    while (std::getline(std::cin, line)) {
        
        Command cmd{line};
        blockPackage.ParseCommand(cmd);

        if (cmd.IsEOF())
            break;
    }

    auto cmdBlock = blockPackage.GetCommandPackage();
    for (const auto v : cmdBlock) {
        v->PrintCommandBlock(std::cout);
        //v.Save();
    }

    return 0;
}