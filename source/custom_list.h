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
	}

	void push_back(const T& value) {
		Allocator::rebind<Node>::other allocator;
		auto node = allocator.allocate(1);
		allocator.construct(node, value, nullptr, m_back);
		//Node* node = new (memory) Node{ value, nullptr, m_back };

		if (nullptr == m_front)
			m_front = node;
		//start
		// Maybe cut to Node::Node next two lines?
		if (nullptr != m_back)
			m_back->m_next = node;
		//end
		
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
};
