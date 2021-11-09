#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <ctime>
#include <fstream>

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
    
public:
    virtual bool IsBlockEmpty() const = 0;

    virtual std::string ToString() const = 0;

protected:
    std::list<Command> m_cmdBlock;
};

class StandartBlockHandler : public BlockHandler {
public:
    StandartBlockHandler() = default;

    void StopBlock(CommandPackage* blockPackagePtr) override;

    void StartDymamicBlock(CommandPackage* blockPackagePtr) override {}

    void EndDymamicBlock(CommandPackage* blockPackagePtr) override {}

    void AddCommandToBlock(CommandPackage* blockPackagePtr, const Command& cmd) override;

    inline bool IsBlockEmpty() const override {
        return m_cmdBlock.empty();
    }

    std::string ToString() const override {
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
        
        if (!m_blockHandlerPtr->IsBlockEmpty()) {
            std::time_t timeNow = std::time(nullptr);
            std::localtime(&timeNow);
            m_cmdPackage.insert({ m_blockHandlerPtr, timeNow});
        }

        m_blockHandlerPtr = blockHandlerPtr;
    }

    int GetBlockSize() const {
        return m_blockSize;
    }

    void Print(std::ostream& out) const {
        for (const auto v : m_cmdPackage) {
            std::this_thread::sleep_for(1000ms);
            out << v.first->ToString();
        }
    }

    void Save() const {
        std::string fileNamePrefix{ "bulk" };
        std::string fileNamePostfix;
        
        std::ofstream fileCmdBlock;
        
        for (const auto v : m_cmdPackage) {
            fileNamePostfix = std::to_string(v.second);
            fileNamePostfix += ".log";
            fileCmdBlock.open(fileNamePrefix + fileNamePostfix, std::ios::binary | std::ios::app);
            
            std::string cmdBlockContent = v.first->ToString();
            fileCmdBlock.write(cmdBlockContent.c_str(), cmdBlockContent.length());
            
            fileCmdBlock.close();
        }
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
    std::map<std::shared_ptr<BlockHandler>, std::time_t> m_cmdPackage;
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

    commandPackage.Print(std::cout);
    commandPackage.Save();


    return 0;
}