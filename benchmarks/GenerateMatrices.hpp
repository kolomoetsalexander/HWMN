#pragma once

#include <cstddef>
#include <cstdint>
#include <random>
#include <stdexcept>
#include <type_traits>

//generate a random square matrix
template<typename MatrixType, typename T>
MatrixType generateRandomMatrix(size_t n, T min, T max, uint32_t seed = 42){
    if (n == 0 || min > max){
        throw std::invalid_argument("Invalid generator parameters");
    }

    MatrixType matrix(n, n);
    std::mt19937 generator(seed);
    //integer
    if constexpr (std::is_integral_v<T>){
        std::uniform_int_distribution<T> distribution(min, max);

        for(size_t i = 0; i < n; ++i){
            for (size_t j = 0; j < n; ++j){
                matrix(i, j) = distribution(generator);
            }
        }
    } 
    //only real
    else{
        std::uniform_real_distribution<T> distribution(min, max);

        for(size_t i = 0; i < n; ++i){
            for(size_t j = 0; j < n; ++j){
                matrix(i, j) = distribution(generator);
            }
        }
    }
    return matrix;
}

//generate an upper triangular matrix with determinant 1
template<typename MatrixType>
MatrixType generateUpperTriangularMatrix(size_t n){
    if (n == 0){
        throw std::invalid_argument("Matrix size must be positive");
    }
    MatrixType matrix(n, n);

    for (size_t i = 0; i < n; ++i){
        matrix(i, i) = 1;
        for (size_t j = i + 1; j < n; ++j){
            matrix(i, j) = static_cast<int>((i + j) % 5);
        }
    }
    return matrix;
}

//generate a singular matrix (det = 0)
template<typename MatrixType, typename T>
MatrixType generateSingularMatrix(size_t n, T min, T max, uint32_t seed = 42){
    MatrixType matrix = generateRandomMatrix<MatrixType>(n, min, max, seed);
    if (n == 1){
        matrix(0, 0) = 0;
    }
    else{
        //duplicate the first row
        for (size_t j = 0; j < n; ++j){
            matrix(n - 1, j) = matrix(0, j);
        }
    }
    return matrix;
}
