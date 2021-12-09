#include "FileSeacher.h"


std::list<std::filesystem::path> FileSeacher::GetAllFilePath() const {
	auto allFilesToCompare = m_dirTraversalPtr->Traversal();
	return allFilesToCompare;
}