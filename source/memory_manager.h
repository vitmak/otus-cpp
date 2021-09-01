#pragma once

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
		/*bool isFree = m_state == MemoryStates::eFree;
		std::cout << m_start << " state: " << isFree << std::endl;*/
	}
	
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
			m_memoryAreas.emplace_back(MemoryArea{start + i});
		}
	}
	
	bool isContain(const T* element) const {
		return m_start <= element && element < (m_start + m_elementsCount);
	}

	T* GetFreeMemory() const {
		for (const auto& v : m_memoryAreas) {
			if (v.GetState() == MemoryStates::eFree)
				return v.GetStart();
		}

		return nullptr;
	}

	void SetState(const T* element, MemoryStates state) {
		auto memArea = const_cast<MemoryArea<T>*> (GetMemoryArea(element));
		if (memArea != nullptr)
			memArea->SetState(state);
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

		_ASSERT(false);
		return nullptr;
	}
};


template<typename T, size_t N>
class MemoryManager {
public:
	MemoryManager() = default;
	~MemoryManager() = default;

	
	T* GetFreeMemory() {
		std::cout << "MemoryManager::GetFreeMemory" << std::endl;
		
		T* freeMemory = nullptr;
		for (const auto& v : m_memoryBlocks) {
			freeMemory = v.GetFreeMemory();
			if (nullptr != freeMemory)
				break;
		}

		if (nullptr == freeMemory) {
			std::cout << "Create new memory block!" << std::endl;
			freeMemory = reinterpret_cast<T*> (std::malloc(N * sizeof(T)));
			if (nullptr == freeMemory)
				throw std::bad_alloc();

			m_memoryBlocks.push_front(MemoryBlock<T, N>{freeMemory});
		}
		
		std::cout << freeMemory << std::endl;
		_ASSERT(nullptr != freeMemory);
		if (nullptr != freeMemory)
			SetMemoryState(freeMemory, MemoryStates::eBusy);

		return freeMemory;
	}

	void SetMemoryState(const T* element, MemoryStates state) {
		for (auto& v : m_memoryBlocks) {
			if (v.isContain(element)) {
				v.SetState(element, state);
				break;
			}
		}
	}

private:
	std::forward_list<MemoryBlock<T, N>> m_memoryBlocks;
};
