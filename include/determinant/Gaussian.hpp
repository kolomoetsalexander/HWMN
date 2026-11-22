#pragma once

#include <cmath>
#include <cstddef>
#include <stdexcept>

template<template<typename> class Container, typename T>
auto gaussian(const Container<T>& matrix){
    
    using R = long double;

    if (matrix.rows() != matrix.cols()){
        throw std::invalid_argument("matrix must be square");
    }

    const size_t n = matrix.rows();

    if (n == 0){
        return R{1};
    }

    Container<R> a(n, n);

    for (size_t i = 0; i < n; ++i){
        for (size_t j = 0; j < n; ++j){
            a(i, j) = static_cast<R>(matrix(i, j));
        }
    }

    R determinant = 1;
    int sign = 1;

    for (size_t k = 0; k < n; ++k){

        //find pivot element
        size_t pivotRow = k;

        for (size_t i = k + 1; i < n; ++i){
            if (std::abs(a(i, k)) > std::abs(a(pivotRow, k))){
                pivotRow = i;
            }
        }

        //singular matrix
        if (a(pivotRow, k) == R{0}){
            return R{0};
        }

        //swap rows
        if (pivotRow != k){
            for (size_t j = 0; j < n; ++j){
                std::swap(a(k, j), a(pivotRow, j));
            }
            sign = -sign;
        }

        const R pivot = a(k, k);
        determinant *= pivot;

        //eliminate elements below the pivot
        for (size_t i = k + 1; i < n; ++i){
            const R factor = a(i, k) / pivot;
            a(i, k) = R{0};

            for (size_t j = k + 1; j < n; ++j){
                a(i, j) -= factor * a(k, j);
            }
        }
    }
    return static_cast<R>(sign * determinant);
}
