#pragma once

#include <map>
#include <utility>


template <typename T, T value>
class Matrix {
public:
	Matrix() = default;
	line& operator [] (size_t rowIndex) const {
		return 
	}

	T& operator = (const T& value){
		
	}

	size_t size() const {
		return m_size;
	}
private:
	class Line{
	public:
		size_t m_Index;
		Line() = default;
		T& operator [] const{

		}
	};
	
	Line m_row;
	Line m_column;
	
	size_t m_size = 0;
};