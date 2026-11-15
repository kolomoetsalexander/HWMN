#include <iostream>
#include "matrix/Matrix.hpp"
#include "matrix/JaggedMatrix.hpp"
#include "determinant/Gaussian.hpp"
#include "determinant/Bareiss.hpp"
#include "benchmarks/Benchmark.hpp"
#include "benchmarks/GenerateMatrices.hpp"

int main(){
    constexpr size_t sizes[] = {50, 100, 200, 300};
    std::cout << "algorithm,layout,size,time_ms\n";

    for (size_t i = 0; i < 4; i++){
        size_t n = sizes[i];
        auto a = generateRandomMatrix<Matrix<double>>(n, -1.0, 1.0, 42);
        auto b = generateRandomMatrix<JaggedMatrix<double>>(n, -1.0, 1.0, 42);
        double timeA = benchmark([&]() {return gaussian(a);});
        double timeB = benchmark([&]() {return gaussian(b);});

        std::cout << "gaussian,contiguous,"<< n << "," << timeA << '\n';
        std::cout << "gaussian,jagged," << n << "," << timeB << '\n';
    }
    constexpr size_t bareissSizes[] = {50, 100, 200, 300};

    for (size_t i = 0; i < 4; i++){
        size_t n = bareissSizes[i];
        auto a = generateUpperTriangularMatrix<Matrix<long long>>(n);
        auto b = generateUpperTriangularMatrix<JaggedMatrix<long long>>(n);
        double timeA = benchmark([&](){return bareiss(a);});
        double timeB = benchmark([&](){return bareiss(b);});

        std::cout << "bareiss,contiguous," << n << "," << timeA << '\n';
        std::cout << "bareiss,jagged," << n << "," << timeB << '\n';
    }
    return 0;
}
