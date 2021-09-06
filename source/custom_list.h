#pragma once

#include <exception>


template<typename T>
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
		Node* node = new Node(value, nullptr, m_back);
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


//template<typename T>
//class List {
//private:
//	struct Node {
//		T* m_data = nullptr;
//		Node* m_next = nullptr;
//		Node* m_prev = nullptr;
//
//		Node(T* data, Node* next, Node* prev) : m_data(data), m_next(next), m_prev(prev) {
//		}
//	};
//
//public:
//	List() = default;
//	~List() {
//		for (auto it = iterator.begin(); it != iter)
//	}
//
//	void push_back(T value) {
//		Node* node = new Node(T, nullptr, m_back);
//		m_back = node;
//	}
//
//	void push_front(T value) {
//		Node* node = new Node(&T, m_front, nullptr);
//		m_back = node;
//	}
//
//	bool empty()const {
//		return nullptr == m_back;
//	}
//	/*Iterator erase() {
//
//	}*/
//
//	class Iterator {
//	public:
//		friend class List;
//		Iterator() = default;
//		~Iterator() = default;
//
//		Iterator operator = (const Iterator& iter) {
//			m_node = iter.m_node;
//			return this;
//		}
//
//		T& operator * () {
//			if (nullptr == m_node)
//				throw std::exception();
//
//			return *m_node->m_data;
//		}
//
//		Iterator operator ++ () {
//			if (nullptr != m_node)
//				m_node = m_node->m_next;
//		}
//
//		bool operator != (const Iterator& rhs) const {
//			return m_node != rhs.m_node;
//		}
//
//	private:
//		Node* m_node = nullptr;
//	};
//
//	Iterator begin() {
//		m_iterator.m_node = m_front;
//		return m_iterator;
//	}
//	/*Iterator end() {
//		m_iterator.m_node = m_back;
//		++m_iterator;
//		return m_iterator;
//	}*/
//
//	//using iterator = Iterator;
//
//private:
//	Node* m_front = nullptr;
//	Node* m_back = nullptr;
//	Iterator m_iterator;
//};