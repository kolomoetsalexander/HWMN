#pragma once

#include <type_traits>

#include "Gaussian.hpp"
#include "Bareiss.hpp"

template<template<typename> class Container, typename T>
auto determinant(const Container<T>& matrix){
    if constexpr (std::is_floating_point_v<T>){
        return gaussian(matrix);
    }
    else{
        return bareiss(matrix);
    }
}
