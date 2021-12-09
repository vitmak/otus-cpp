#pragma once

#include "Config.h"
#include "DirectoryTraversal.h"
#include <memory>
#include <filesystem>
#include <string>
#include <list>



class Config;


class FileSeacher {
public:
	FileSeacher(std::unique_ptr<DirectoryTraversalBase> dirTraversalPtr) : m_dirTraversalPtr(std::move(dirTraversalPtr)) {
		
	}

	std::list<std::filesystem::path> GetAllFilePath() const; // MayBe: instead std::string use std::filesystem::path?

private:
	std::unique_ptr<DirectoryTraversalBase> m_dirTraversalPtr;
};