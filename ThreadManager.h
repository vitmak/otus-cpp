#pragma once

#include "Logger.h"
#include "ConsoleLogger.h"
#include "FileLogger.h"
#include <thread>


class ThreadManager {
public:
	ThreadManager()
	{
		const auto& consoleLogger = std::make_shared<ConsoleLogger>();
		std::thread threadLog{ &Logger::Logging, consoleLogger };
		m_threadLog = std::move(threadLog);

		const auto& fileLogger = std::make_shared<FileLogger>();
		std::thread threadFile1{ &Logger::Logging, fileLogger };
		m_threadFile1 = std::move(threadFile1);
		
		std::thread threadFile2{ &Logger::Logging, fileLogger };
		m_threadFile2 = std::move(threadFile2);

		m_loggers.push_back(consoleLogger);
		m_loggers.push_back(fileLogger);
	}

	~ThreadManager() {
		
		NotifyStopping();

		m_threadLog.join();
		m_threadFile1.join();
		m_threadFile2.join();
	}

	void NotifyStopping() {
		for (const auto& v : m_loggers)
			v->m_queue.NotifyStopping();
	}

	void AddToLogging(const std::shared_ptr<BlockHandler>& blockHandler) {
		for (const auto& v : m_loggers)
			v->m_queue.Push(blockHandler);
	}

private:
	std::thread m_threadLog;
	std::thread m_threadFile1;
	std::thread m_threadFile2;

	std::list<std::shared_ptr<Logger>> m_loggers;
};