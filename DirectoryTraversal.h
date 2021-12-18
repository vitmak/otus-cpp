#pragma once

#include "Config.h"
#include <iostream>
#include <filesystem>
#include <list>
#include <regex>

using namespace std::literals;


class DirectoryTraversalBase {
public:
	virtual std::list<std::filesystem::path> Traversal() = 0;
	virtual ~DirectoryTraversalBase(){}
};


template <typename IteratorType>
class DirectoryTraversal : public DirectoryTraversalBase {
public:
	DirectoryTraversal(const Config& config) : m_refConfig(config) {
	}

	bool IsExlude(const std::string& path) const {
		// Check exclude dir
		for (const auto& excludeDir : m_refConfig.m_excludeDirs) {
			if (path.starts_with(excludeDir))
				return true;
		}
		return false;
	}

	std::list<std::filesystem::path> Traversal() override {
		std::list<std::filesystem::path> allFilePath;

		std::string allFileMasks;
		for (auto it = m_refConfig.m_fileMasks.cbegin(); it != m_refConfig.m_fileMasks.cend(); ++it) {
			if (it != m_refConfig.m_fileMasks.cbegin())
				allFileMasks += '|';
			for (auto symbol : *it) {
				if (symbol == '*')
					allFileMasks += "\\w*";
				else if (symbol == '?')
					allFileMasks += "\\w";
				else if (symbol == '.')
					allFileMasks += "\\.";
				else
					allFileMasks += symbol;
			}
		}

		auto prefix = "^[\\w\\:\\\\]*(?:"s;
		auto suffix = ")$"s;

		//  ^[\w\:\\]*(?:fileMask1|fileMask2 ...)$
		const auto pattern = std::move(prefix) + std::move(allFileMasks) + std::move(suffix);
		static const std::regex regularPattern{ pattern, std::regex_constants::ECMAScript | std::regex_constants::icase };
		// end RegexPattern

		for (const auto& dirPath : m_refConfig.m_includeDirs) {
			for (auto const& dirEntry : IteratorType{ dirPath }) {
				std::string directoryPath = dirEntry.path().string();
				if (IsExlude(directoryPath))
					continue;

				if (dirEntry.is_regular_file()) {
					if (file_size(dirEntry.path()) < m_refConfig.m_minFileSize)
						continue;
					
						if (std::regex_search(directoryPath, regularPattern)) {
							allFilePath.push_back(dirEntry.path());
					}
				}
			}
		}

		return allFilePath;
	}

	~DirectoryTraversal() = default;

private:
	const Config& m_refConfig;
};