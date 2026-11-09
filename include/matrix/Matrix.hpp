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
    Matrix(size_t rows, size_t cols): rows_(rows), cols_(cols), data_(nullptr){
        if(rows == 0 || cols == 0){
            throw std::invalid_argument("cols&rows must be positive");
        }
        const size_t maxSize = std::numeric_limits<size_t>::max();

        if(rows > maxSize / cols){
            throw std::length_error("size overflow");
        }
        const size_t count = rows * cols;

        if(count > maxSize / sizeof(T)){
            throw std::length_error("allocation size overflow");
        }
        data_ = new T[count]{};
    }

    ~Matrix(){
        delete[] data_;
    }

    Matrix(const Matrix& other): rows_(other.rows_), cols_(other.cols_), data_(nullptr){
        if (other.data_ == nullptr){
            return;
        }

        const size_t count = rows_ * cols_;
        T* newData = new T[count]{};

        try{
            std::copy(other.data_, other.data_ + count, newData);
        }
        catch(...){
            delete[] newData;
            throw;
        }
        data_ = newData;
    }

    Matrix& operator=(const Matrix& other){
        if (this == &other){
            return *this;
        }
        Matrix temp(other);
        swap(temp);

        return *this;
    }

    Matrix(Matrix&& other) noexcept: rows_(other.rows_), cols_(other.cols_), data_(other.data_){
        other.rows_ = 0;
        other.cols_ = 0;
        other.data_ = nullptr;
    }

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
        if (row >= rows_ || col >= cols_){
            throw std::out_of_range("indexes out of range");
        }
        return data_[row * cols_ + col];
    }

    const T& operator()(size_t row, size_t col) const{
        if (row >= rows_ || col >= cols_){
            throw std::out_of_range("indexes out of range");
        }
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