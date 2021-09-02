#pragma once

#include <iostream>
#include <vector>
#include <forward_list>

enum class MemoryStates {
	eBusy = 0,
	eFree
};

template<typename T>
class MemoryArea {
public:
	MemoryArea(T* start) : m_start(start) {
		bool isFree = m_state == MemoryStates::eFree;
		std::cout << m_start << " state: " << isFree << std::endl;
	}

	/*bool operator== (const MemoryArea<T>& rhs) const {
		return m_start == rhs.m_start && m_state == rhs.m_state;
	}*/
	
	MemoryStates GetState() const {
		return m_state;
	}

	void SetState(MemoryStates state) {
		m_state = state;
	}

	const MemoryArea<T>* GetMemoryArea() const {
		return this;
	}

	T* GetStart() const {
		return m_start;
	}

	bool isContain(const T* element) const {
		return (m_start <= element && element < m_start + 1);
	}

private:
	T* m_start = nullptr;
	MemoryStates m_state = MemoryStates::eFree;
};


template <typename T, size_t N>
class MemoryBlock {
public:
	MemoryBlock(T* start) : m_start(start) {
		std::cout << "Create memory block with start: " << m_start << std::endl;
		m_memoryAreas.reserve(m_elementsCount);
		for (auto i = 0; i < m_elementsCount; ++i) {
			m_memoryAreas.emplace_back(MemoryArea<T>{start + i});
		}
	}

	//--
	void ShowBlockStates() const {
		for (const auto& v : m_memoryAreas) {
			bool isFree = v.GetState() == MemoryStates::eFree;
			std::cout << v.GetStart() << " state: " << isFree << std::endl;
		}
	}
	//--
	
	bool isContain(const T* element) const {
		return m_start <= element && element < (m_start + m_elementsCount);
	}

	T* GetFreeMemory(size_t elementsCount) const {
		for (auto it = m_memoryAreas.cbegin(); it != m_memoryAreas.cend(); ++it) {
			auto sequence = 0;
			for (auto iter = it; iter != m_memoryAreas.cend(); ++iter) {
				if (iter->GetState() == MemoryStates::eFree) {
					if (++sequence == elementsCount)
						return it->GetStart();
				}
				else
					break;					
			}
		}

		return nullptr;
	}

	void SetState(const T* startAddr, size_t elementsCount, MemoryStates state) {
		auto memArea = const_cast<MemoryArea<T>*> (GetMemoryArea(startAddr));
		if (memArea != nullptr) {
			//auto it = std::find(m_memoryAreas.begin(), m_memoryAreas.end(), memArea);
			for (auto it = m_memoryAreas.begin(); it != m_memoryAreas.end(); ++it) {
				if (it->GetStart() == memArea->GetStart() && it->GetState() == memArea->GetState()) {
					for (; it != m_memoryAreas.end(); ++it) {
						it->SetState(state);
						if (--elementsCount == 0)
						break;
					}
				}
			}
		}
	}
	
private:
	T* m_start;
	const size_t m_elementsCount = N;
	std::vector <MemoryArea<T>> m_memoryAreas;

	const MemoryArea<T>* GetMemoryArea(const T* element) const {
		if (!isContain(element))
			return nullptr;

		for (const auto& v : m_memoryAreas) {
			if (v.isContain(element))
				return v.GetMemoryArea();
		}

		return nullptr;
	}
};


template<typename T, size_t N>
class MemoryManager {
public:
	MemoryManager() = default;
	~MemoryManager() {
		for (auto& v : m_memoryBlocks) {

		}
	}

	T* GetFreeMemory(size_t elementsCount) {
		std::cout << "MemoryManager::GetFreeMemory" << std::endl;
		
		T* startAddr = nullptr;
		for (const auto& v : m_memoryBlocks) {
			v.ShowBlockStates();
			startAddr = v.GetFreeMemory(elementsCount);
			if (nullptr != startAddr) {
				std::cout << "Find free memory in the current block: " << startAddr << std::endl;
				break;
			}
		}

		if (nullptr == startAddr) {
			std::cout << "Create new memory block!" << std::endl;
			startAddr = reinterpret_cast<T*> (std::malloc(N * sizeof(T)));
			if (nullptr == startAddr)
				throw std::bad_alloc();

			m_memoryBlocks.push_front(MemoryBlock<T, N>{startAddr});
		}
		
		SetMemoryState(startAddr, elementsCount, MemoryStates::eBusy);
		return startAddr;
	}

	void SetMemoryState(const T* startAddr, size_t count, MemoryStates state) {
		for (auto& v : m_memoryBlocks) {
			if (v.isContain(startAddr)) {
				v.SetState(startAddr, count, state);
				break;
			}
		}
	}

private:
	std::forward_list<MemoryBlock<T, N>> m_memoryBlocks;
};
