#pragma once

#include <algorithm>
#include <cstddef>
#include <limits>
#include <stdexcept>
#include <utility>

template<typename T>
class Matrix{
private:
    size_t rows_;
    size_t cols_;
    T* data_;

public:
//constructor
    Matrix(size_t rows, size_t cols): rows_(rows), cols_(cols), data_(nullptr){
        const size_t count = rows * cols;
        data_ = new T[count]{};
    }
//destructor
    ~Matrix(){
        delete[] data_;
    }
//copy constructor
    Matrix(const Matrix& other): rows_(other.rows_), cols_(other.cols_), data_(nullptr){
        if (other.data_ == nullptr){
            return;
        }

        const size_t count = rows_ * cols_;
        T* newData = new T[count]{};

        for (size_t i = 0; i < count; ++i){
            newData[i] = other.data_[i];
        }
        data_ = newData;
    }
//copy assigment
    Matrix& operator=(const Matrix& other){
        if (this == &other){
            return *this;
        }
        Matrix temp(other);
        swap(temp);

        return *this;
    }
//moving constructor
    Matrix(Matrix&& other) noexcept: rows_(other.rows_), cols_(other.cols_), data_(other.data_){
        other.rows_ = 0;
        other.cols_ = 0;
        other.data_ = nullptr;
    }
//move assigment
    Matrix& operator=(Matrix&& other) noexcept{
        if (this == &other){
            return *this;
        }
        delete[] data_;
        rows_ = other.rows_;
        cols_ = other.cols_;
        data_ = other.data_;

        other.rows_ = 0;
        other.cols_ = 0;
        other.data_ = nullptr;

        return *this;
    }

    T& operator()(size_t row, size_t col){
        return data_[row * cols_ + col];
    }

    const T& operator()(size_t row, size_t col) const{
        return data_[row * cols_ + col];
    }
    size_t rows() const noexcept{
        return rows_;
    }
    size_t cols() const noexcept{
        return cols_;
    }

    void swap(Matrix& other) noexcept{
        using std::swap;
        swap(rows_, other.rows_);
        swap(cols_, other.cols_);
        swap(data_, other.data_);
    }
};