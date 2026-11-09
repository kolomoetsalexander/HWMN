#pragma once

#include <cstddef>
#include <limits>
#include <stdexcept>
#include <utility>

template<typename T>
class JaggedMatrix{
private:
    size_t rows_;
    size_t cols_;
    T** data_;

    void release() noexcept{
        if (data_ == nullptr){
            return;
        }
        for (size_t i = 0; i < rows_; ++i){
            delete[] data_[i];
        }
        delete[] data_;
        data_ = nullptr;
    }

public:
    //constructor
    JaggedMatrix(size_t rows, size_t cols): rows_(rows), cols_(cols), data_(nullptr){

        if (rows == 0 || cols == 0){
            throw std::invalid_argument("cols&rows must be positive");
        }
        const size_t maxSize = std::numeric_limits<size_t>::max();

        if (rows > maxSize / sizeof(T*)){
            throw std::length_error("allocation size overflow");
        }

        if (cols > maxSize / sizeof(T)){
            throw std::length_error("allocation size overflow");
        }

        data_ = new T*[rows_]{};
        for (size_t i = 0; i < rows_; ++i){
                data_[i] = new T[cols_]{};
            }
    }

    //destructor
    ~JaggedMatrix(){
        release();
    }

    //copy constructor
    JaggedMatrix(const JaggedMatrix& other): rows_(other.rows_), cols_(other.cols_), data_(nullptr){

        if (other.data_ == nullptr){
            return;
        }
        data_ = new T*[rows_]{};

        for (size_t i = 0; i < rows_; ++i){
            data_[i] = new T[cols_]{};
            for (size_t j = 0; j < cols_; ++j){
                data_[i][j] = other.data_[i][j];
            }
        }
        
    }

    //copy assignment
    JaggedMatrix& operator=(const JaggedMatrix& other){
        if (this == &other){
            return *this;
        }

        JaggedMatrix temp(other);
        swap(temp);
        return *this;
    }

    //move constructor
    JaggedMatrix(JaggedMatrix&& other) noexcept: rows_(other.rows_), cols_(other.cols_), data_(other.data_){
        other.rows_ = 0;
        other.cols_ = 0;
        other.data_ = nullptr;
    }

    //move assignment
    JaggedMatrix& operator=(JaggedMatrix&& other) noexcept{
        if (this == &other){
            return *this;
        }
        release();
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
        return data_[row][col];
    }

    const T& operator()(size_t row, size_t col) const{
        if (row >= rows_ || col >= cols_){
            throw std::out_of_range("indexes out of range");
        }

        return data_[row][col];
    }
    size_t rows() const noexcept{
        return rows_;
    }
    size_t cols() const noexcept{
        return cols_;
    }

    void swap(JaggedMatrix& other) noexcept{
        std::swap(rows_, other.rows_);
        std::swap(cols_, other.cols_);
        std::swap(data_, other.data_);
    }
};