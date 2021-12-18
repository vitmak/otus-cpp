#pragma once

#include "Hasher.h"
#include <vector>
#include <list>
#include <map>
#include <filesystem>
#include <fstream>


class HashedFile {
public:
	HashedFile(const std::filesystem::path& filePath, uint32_t blockSize, std::shared_ptr<Hasher> hasherPtr);

	bool IsIdentical(const HashedFile& rhs) const;

	inline std::filesystem::path GetFilePath() const {
		return m_filePath;
	}

private:
	 std::vector<uint8_t> GetHashedBlock(int blockNumber) const;

private:
	uintmax_t m_fileSize;
	uintmax_t m_blockSize;
	std::filesystem::path m_filePath;
	mutable std::vector<std::vector<uint8_t>> m_hashedBlocks;

	mutable std::ifstream m_fileReader;

	std::shared_ptr<Hasher> m_hasherPtr;
};
