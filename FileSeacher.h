#pragma once

#include "Config.h"
#include "DirectoryTraversal.h"
#include "HashedFile.h"
#include <memory>
#include <filesystem>
#include <string>
#include <list>


class Config;

class DuplicateFilesSeacher {
public:
	DuplicateFilesSeacher(const Config& config, std::unique_ptr<DirectoryTraversalBase> dirTraversalPtr) : m_dirTraversalPtr(std::move(dirTraversalPtr)), m_refConfig{ config } {
	}

	std::list<std::filesystem::path> GetDuplicates() const;

private:
	std::list<std::filesystem::path> GetAllFilePath() const;

private:
	std::unique_ptr<DirectoryTraversalBase> m_dirTraversalPtr;
	const Config& m_refConfig;
};
