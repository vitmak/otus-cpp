#pragma once

#include<map>
#include<vector>

template<typename T, size_t N>
class MemoryManager {
public:
	MemoryManager() = default;
	~MemoryManager() {
		/*for (const auto& v : m_memoryBlocks) {
			if (v.second)
				turn v.first;
		}*/
	}

	T* GetFreeMemory() {
		std::cout << (pFreeMemory + i) << std::endl;
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		for (const auto& v : m_memoryBlocks) {
			if (v.second) {
				
				return v.first;
			}
				
		}
		
		auto pFreeMemory = reinterpret_cast<T*> (std::malloc(N * sizeof(T)));
		if (nullptr == pFreeMemory)
			throw std::bad_alloc();

		
		for (auto i = 0; i < N; ++i) {
			std::cout << (pFreeMemory + i) << std::endl;
			m_memoryBlocks.insert({ reinterpret_cast<T*>(pFreeMemory + i), true });
		}
			
		std::cout << (pFreeMemory + i) << std::endl;
		return pFreeMemory;
	}

	void SetMemoryState(T* pElement, bool bState) {
		auto it = m_memoryBlocks.find(pElement);
		
		//assert(it != m_memoryBlocks.end());
		if (it != m_memoryBlocks.end())
			it->second = bState;
	}

private:
	std::map<T*, bool> m_memoryBlocks;
};
