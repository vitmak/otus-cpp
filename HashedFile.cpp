#include "HashedFile.h"


HashedFile::HashedFile(const std::filesystem::path& filePath, uint32_t blockSize, std::shared_ptr<Hasher> hasherPtr)
	: m_filePath{ filePath }, m_blockSize{ blockSize }, m_fileReader{ filePath.string() }, m_hasherPtr{hasherPtr}
{
	m_fileSize = file_size(m_filePath);

	auto blocks = m_fileSize / m_blockSize;
	if (blocks == 0)
		blocks = 1;
	else if (m_fileSize % m_blockSize != 0)
		++blocks;
	m_hashedBlocks.reserve(blocks);
}

std::vector<uint8_t> HashedFile::GetHashedBlock(int blockNumber) const {
	if (blockNumber < m_hashedBlocks.size())
		return m_hashedBlocks[blockNumber];
	
	std::vector<uint8_t> buffer (m_blockSize, 0);
	
	m_fileReader.read((char*)buffer.data(), m_blockSize);

	auto hashBlock = m_hasherPtr->HashBlock(buffer);
	m_hashedBlocks.emplace_back(hashBlock);
	return hashBlock;
}

bool HashedFile::IsIdentical(const HashedFile& rhs) const {
	if (m_fileSize != rhs.m_fileSize)
		return false;
	
	for (auto blockNum = 0; blockNum < m_hashedBlocks.capacity(); ++blockNum) {
		if (GetHashedBlock(blockNum) != rhs.GetHashedBlock(blockNum))
			return false;
	}

	return true;
}