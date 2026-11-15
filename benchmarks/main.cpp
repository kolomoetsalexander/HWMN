#include <iostream>
#include "matrix/Matrix.hpp"
#include "matrix/JaggedMatrix.hpp"
#include "determinant/Gaussian.hpp"
#include "benchmarks/Benchmark.hpp"
#include "benchmarks/GenerateMatrices.hpp"

int main(){
    constexpr size_t sizes[] = {50, 100, 200, 300};
    std::cout << "algorithm,layout,size,time_ms\n";

    for (size_t n : sizes){
        auto a = generateRandomMatrix<Matrix<double>>(n, -1.0, 1.0, 42);
        auto b = generateRandomMatrix<JaggedMatrix<double>>(n, -1.0, 1.0, 42);
        double timeA = benchmark([&]() {return gaussian(a);});
        double timeB = benchmark([&]() {return gaussian(b);});

        std::cout << "gaussian,contiguous,"<< n << "," << timeA << '\n';
        std::cout << "gaussian,jagged," << n << "," << timeB << '\n';
    }
    return 0;
}
