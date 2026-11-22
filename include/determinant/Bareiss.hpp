#pragma once

#include <cstddef>
#include <stdexcept>
#include <type_traits>
#include <utility>

template<template<typename> class Container, typename T>
auto bareiss(const Container<T>& matrix){

    using R = long long;

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
            a(i, j) = matrix(i, j);
        }
    }

    R previousPivot = 1;
    int sign = 1;

    for (size_t k = 0; k + 1 < n; ++k){

        //find pivot element
        size_t pivotRow = k;

        while (pivotRow < n && a(pivotRow, k) == 0){
            ++pivotRow;
        }

        //singular matrix
        if (pivotRow == n){
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

        //bareiss formula
        for (size_t i = k + 1; i < n; ++i){
            for (size_t j = k + 1; j < n; ++j){

                const R numerator =pivot * a(i, j) - a(i, k) * a(k, j);
                a(i, j) = numerator / previousPivot;
            }
            a(i, k) = 0;
        }
        previousPivot = pivot;
    }
    const R result = sign * a(n - 1, n - 1);
    return result;
}
