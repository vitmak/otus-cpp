#pragma once

#include <map>
#include <tuple>
#include <utility>


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
        int m_rowIndex = 0;
        Matrix* m_matrixPtr;
    };

public:

    Matrix() = default;
    MatrixItem<T>& GetMatrixItem(const MatrixCell& matrCell) {
        auto itFind = m_Items.find(matrCell);
        if (itFind == m_Items.end()) {
            auto [it, status] = m_Items.insert({ matrCell, MatrixItem{defaultValue} });
            return it->second;
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
    //class Iterator {
    //    
    //public:
    //    Iterator() = default;
    //    // For methods Matrix::begin / Matrix::End 
    //    Iterator(typename MatrixLines::iterator linesIter, bool isInitItemPtr = false) : m_linesIter{ linesIter } {
    //        if (isInitItemPtr)
    //            m_lineItemsPtr = m_linesIter->second.begin();
    //    }

    //    bool operator == (const Iterator& rhs) const {
    //        bool res = m_linesIter == rhs.m_linesIter && m_lineItemsPtr == rhs.m_lineItemsPtr;
    //        return m_linesIter == rhs.m_linesIter && m_lineItemsPtr == rhs.m_lineItemsPtr;
    //    }

    //    /*bool operator != (const Iterator& rhs) const {
    //        return !(*this == rhs);
    //    }*/
    //    /*
    //    Iterator& operator++ () {
    //        if (m_matrixIter != m_matrixLines.end())
    //            ++m_matrixIter;
    //    }*/

    //private:     
    //    typename MatrixLines::iterator m_linesIter;
    //    typename LineItems::iterator m_lineItemsPtr;
    //};

    //Iterator begin() {
    //    return Iterator{ m_matrixLines.begin() };
    //}

    //Iterator end() {
    //    return Iterator{ m_matrixLines.end() };
    //}
};
