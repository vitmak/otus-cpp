#pragma once

#include <string>

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
