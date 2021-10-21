#pragma once

#include <map>
#include <tuple>
#include <utility>
#include <stdexcept>


template<typename T>
class MatrixItem {
public:
    MatrixItem(const T& value) : m_value{ value } {}

    MatrixItem& operator = (const T& value) {
        m_value = value;
        return *this;
    }

    T& GetValue() {
        return m_value;
    }

private:
    T m_value;
};


struct MatrixCell {
    int m_rowIndex = 0;
    int m_columnIndex = 0;
    bool m_busy = false;

    bool operator < (const MatrixCell& rhs)const {
        return m_rowIndex == rhs.m_rowIndex ? m_columnIndex < rhs.m_columnIndex : m_rowIndex < rhs.m_rowIndex;
    }
};


template <typename T, T defaultValue>
class Matrix {
public:
    class MatrixItemGetter {
    public:
        MatrixItemGetter(Matrix* matrixPtr, int rowIndex) : m_matrixPtr{ matrixPtr }, m_rowIndex{rowIndex} {
        }

        MatrixItem<T>& operator [] (int columnIndex) {
            return m_matrixPtr->GetMatrixItem(MatrixCell{m_rowIndex, columnIndex});
        }

    private:
        Matrix* m_matrixPtr = nullptr;
        int m_rowIndex = 0;
    };

public:

    Matrix() = default;
    MatrixItem<T>& GetMatrixItem(const MatrixCell& matrCell) {
        auto itFind = m_Items.find(matrCell);
        
        if (itFind == m_Items.end()) {
            auto insert = m_Items.insert(/*paIns*/{ matrCell, MatrixItem<T>{defaultValue} });
            if (!insert.second)
                throw std::bad_alloc();
            return insert.first->second;
        }

        return itFind->second;
    }

    MatrixItemGetter operator [] (int rowIndex) {
        return MatrixItemGetter{this, rowIndex};
    }

    size_t size() {
        size_t matrixSize = 0;
        for (auto& v : m_Items) {
            if (v.second.GetValue() != defaultValue)
                ++matrixSize;
        }

        return matrixSize;
    }

private:
    std::map<MatrixCell, MatrixItem<T>> m_Items;

public:
    class Iterator {
        using MatrixItems = std::map<MatrixCell, MatrixItem<T>>;
    public:
        Iterator() = default;

        Iterator(typename MatrixItems::iterator itemsIter) : m_itemsIter{ itemsIter } {
        }

        bool operator == (const Iterator& rhs) const {
            return m_itemsIter == rhs.m_itemsIter;
        }

        bool operator != (const Iterator& rhs) const {
            return !(*this == rhs);
        }
        
        Iterator& operator++ () {
            ++m_itemsIter;
            return *this;
        }

        std::tuple<int, int, T> operator* () {
            while (m_itemsIter->second.GetValue() == defaultValue)
                operator++();
            return std::make_tuple(m_itemsIter->first.m_rowIndex, m_itemsIter->first.m_columnIndex, m_itemsIter->second.GetValue());
        }

    private:     
        typename MatrixItems::iterator m_itemsIter;
    };

    Iterator begin() {
        return Iterator{ m_Items.begin() };
    }

    Iterator end() {
        return Iterator{ m_Items.end() };
    }
};
