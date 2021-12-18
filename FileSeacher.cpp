#include "FileSeacher.h"
#include "HashedFile.h"
#include "CRC32Hasher.h"
#include "MD5Hasher.h"
#include <map>
#include <fstream>
#include <algorithm>


std::list<std::filesystem::path> DuplicateFilesSeacher::GetAllFilePath() const {
	auto allFilesToCompare = m_dirTraversalPtr->Traversal();
	return allFilesToCompare;
}


std::list<std::filesystem::path> DuplicateFilesSeacher::GetDuplicates() const {
	auto allFilesToCmp = GetAllFilePath();

	std::list<std::filesystem::path> duplicates;

	if (allFilesToCmp.empty() || allFilesToCmp.size() == 1)
		return duplicates;

	std::shared_ptr<Hasher> hasher = nullptr;
	if (m_refConfig.m_hashAlgorithm == "crc32")
		hasher = std::make_shared<CRC32Hasher>(CRC32Hasher{});
	else
		hasher = std::make_shared<MD5Hasher>(MD5Hasher{});

	std::list<HashedFile> filesToCompare;
	for (const auto& filePath : allFilesToCmp) {
		filesToCompare.emplace_back(HashedFile{ filePath, m_refConfig.m_blockSize, hasher });
	}
	
	for (auto itLhs = filesToCompare.cbegin(); itLhs != filesToCompare.cend(); ++itLhs) {
		bool isDuplicate = false;

		if (duplicates.cend() != std::find(duplicates.cbegin(), duplicates.cend(), itLhs->GetFilePath()))
			continue;

		for (auto itRhs = filesToCompare.cbegin(); itRhs != filesToCompare.cend(); ++itRhs) {
			if (itLhs == itRhs)
				continue;

			if (itLhs->IsIdentical(*itRhs)) {
				if (!isDuplicate) {
					duplicates.emplace_back(itLhs->GetFilePath());
					isDuplicate = true;
				}

				duplicates.emplace_back(itRhs->GetFilePath());
			}
		}
	}

	return duplicates;
}