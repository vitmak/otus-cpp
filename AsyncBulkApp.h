#pragma once

#include "CommandPackage.h"
#include <string>


class AsyncBulkApp {
public:
	AsyncBulkApp(size_t bulkSize) : m_cmdPackage{ static_cast<int>(bulkSize) }  {
		static int bulkAppNumber = 0;
		m_cmdPackage.SetContextID(++bulkAppNumber);
	}

	void ReadBuffer(const char* data, std::size_t size) {
		std::string cmdName;

		if (!m_buffer.empty())
			std::swap(m_buffer, cmdName);
	
		for (size_t i = 0; i < size; ++i) {
			if (data[i] != '\n')
				cmdName += data[i];
			else {
				if (!cmdName.empty()) {
					m_cmdPackage.ParseCommand(Command{cmdName});
					cmdName = "";
				}
			}
		}

		if (!cmdName.empty())
			std::swap(m_buffer, cmdName);
	}

private:
	std::string m_buffer;
	CommandPackage m_cmdPackage;
};