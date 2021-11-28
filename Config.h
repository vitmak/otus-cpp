#pragma once

#include <string>
#include <vector>


class Config {
public:
    enum class ScanLevel {
        Current = 0,
        All = 1
    };

    static Config ParseCmdArguments(int argc, const char* argv[]);

public:
    bool m_showHelp;
    std::string m_helpText;
    std::vector<std::string> m_incudeDirs;
    std::vector<std::string> m_excludeDirs;
    ScanLevel m_scanLevel;
    unsigned int m_minFileSize = 1;
    std::vector<std::string> m_fileMasks;
    unsigned int m_blockSize;
    std::string m_hashAlgorithm;

private:
    Config() = default;
};