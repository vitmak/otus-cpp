#pragma once

#include "Config.h"
#include <iostream>
#include <filesystem>
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

	// maybe: use std::filesystem::path
	std::list<std::filesystem::path> Traversal() override {
		std::list<std::filesystem::path> allFilePath;

		// begin RegexPattern
		auto prefix = "^[\\w\\:\\\\]*(?:"s;
		auto suffix = ")\\w*\\.\\w+$"s;

		std::string allFileMasks;
		for (auto it = m_refConfig.m_fileMasks.cbegin(); it != m_refConfig.m_fileMasks.cend(); ++it) {
			if (it != m_refConfig.m_fileMasks.cbegin())
				allFileMasks += "|";
			allFileMasks += *it;
		}

		//  ^[\w\:\\]*(?:fileMask1|fileMask2 ...)\w*\.\w+$
		const auto pattern = std::move(prefix) + std::move(allFileMasks) + std::move(suffix);
		static const std::regex regularPattern{ pattern, std::regex_constants::ECMAScript | std::regex_constants::icase };
		// end RegexPattern

		for (const auto& dirPath : m_refConfig.m_includeDirs) {
			for (auto const& dirEntry : IteratorType{ dirPath }) {
				std::cout << dirEntry << '\n';
				std::string directoryPath = dirEntry.path().string();
				if (IsExlude(directoryPath))
					continue;

				if (dirEntry.is_regular_file()) {
					auto fileSize = file_size(dirEntry.path());
					//if (file_size(dirEntry.path()) < m_refConfig.m_minFileSize)
					if (fileSize < m_refConfig.m_minFileSize)
						continue;
					
						if (std::regex_search(directoryPath, regularPattern)) {
							allFilePath.push_back(dirEntry.path());
					}
				}
			}
		}

		return allFilePath;
	}

	~DirectoryTraversal() {
		std::cout << "~DirectoryTraversal" << std::endl;
	}

private:
	const Config& m_refConfig;
};