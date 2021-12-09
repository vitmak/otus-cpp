#pragma once

#include <string>
#include <vector>


enum class ScanLevel {
    Current = 0,
    All = 1
};

class Config {
public:
    static Config ParseCmdArguments(int argc, const char* argv[]);

public:
    bool m_showHelp;
    std::string m_helpText;
    std::vector<std::string> m_includeDirs;
    std::vector<std::string> m_excludeDirs;
    ScanLevel m_scanLevel;
    unsigned int m_minFileSize = 1;
    std::vector<std::string> m_fileMasks;
    unsigned int m_blockSize;
    std::string m_hashAlgorithm;

private:
    Config() = default;
};