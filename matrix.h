#pragma once

#include <map>
#include <list>
#include <utility>


template<typename T>
class MatrixItem {
public:
    MatrixItem(const T& value) : m_value{ value } {}

    MatrixItem& operator = (const T& value) {
        m_value = value;
        return *this;
    }

private:
    T m_value;
};


template <typename T, T defaultValue>
class Matrix {
public:

    class MatrixLine {
    public:

        MatrixLine() = default;
        MatrixItem<T>& operator [] (int columnIndex) {
            auto itFind = m_lineItems.find(columnIndex);
            if (itFind == m_lineItems.end()) {
                MatrixItem<T> item{ defaultValue };
                auto [itInsert, ok] = m_lineItems.insert({ columnIndex, item });
                return itInsert->second;
            }
            
            return itFind->second;
        }

    private:
        std::map<int/*columnIndex*/, MatrixItem<T>> m_lineItems;
    };

public:
    Matrix() = default;

    MatrixLine& operator [] (int rowIndex) {
        auto itFind = m_matrixLines.find(rowIndex);
        if (itFind == m_matrixLines.end()) {
            MatrixLine matrLine{};
            auto [itInsert, isOk] = m_matrixLines.insert({ rowIndex, matrLine });
            return itInsert->second;
        }

        return itFind->second;
    }

private:
    std::map<int/*rowIndex*/, MatrixLine> m_matrixLines;
};
