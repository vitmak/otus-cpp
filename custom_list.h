#pragma once

#include "reserving_allocator.h"
#include <exception>



template<typename T, typename Allocator = std::allocator<T>>
class List {
private:
	struct Node {
		T m_data;
		Node* m_next = nullptr;
		Node* m_prev = nullptr;

		Node(const T& data, Node* next, Node* prev) : m_data(data), m_next(next), m_prev(prev) {
		}
	};

public:
	
	class iterator {
	public:
		friend class List;

		iterator() = default;

		T& operator * () {
			if (nullptr == m_node)
				throw std::exception(); //TODO: add text
			return m_node->m_data;
		}

		iterator& operator ++ () {
			m_node = m_node == nullptr ? nullptr : m_node->m_next;
			return *this;
		}

		bool operator != (const iterator& rhs) const {
			return m_node != rhs.m_node;
		}

	private:
		Node* m_node = nullptr;
	};
	
	
	List() = default;
	~List() {
		while (nullptr != m_front) {
			Node* front = m_front;
			m_front = front->m_next;
			m_allocator.destroy(front);
			m_allocator.deallocate(front, 1);
		}
	}

	void push_back(const T& value) {
		auto node = m_allocator.allocate(1);
		m_allocator.construct(node, value, nullptr, m_back);
		
		if (nullptr == m_front)
			m_front = node;
		
		if (nullptr != m_back)
			m_back->m_next = node;
		
		m_back = node;
	}

	iterator begin() {
		m_iter.m_node = m_front;
		return m_iter;
	}

	iterator end() {
		m_iter.m_node = nullptr == m_back ? nullptr : m_back->m_next;
		return m_iter;
	}

private:
	Node* m_front = nullptr;
	Node* m_back = nullptr;

	iterator m_iter;

	typename Allocator::template rebind<Node>::other m_allocator;
};
