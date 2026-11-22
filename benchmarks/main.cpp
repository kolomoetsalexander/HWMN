#include <benchmark/benchmark.h>

#include "matrix/Matrix.hpp"
#include "matrix/JaggedMatrix.hpp"
#include "determinant/Gaussian.hpp"
#include "determinant/Bareiss.hpp"
#include "benchmarks/GenerateMatrices.hpp"

//dense matrix for Bareiss and Gauss
template<typename MatrixType>
void BM_Gaussian(benchmark::State& state){
    auto matrix = generateDenseMatrix<MatrixType>(
        state.range(0)
    );

    for (auto _ : state){
        benchmark::DoNotOptimize(gaussian(matrix));
    }
}

template<typename MatrixType>
void BM_Bareiss(benchmark::State& state){
    auto matrix = generateDenseMatrix<MatrixType>(
        state.range(0)
    );

    for (auto _ : state){
        benchmark::DoNotOptimize(bareiss(matrix));
    }
}

BENCHMARK_TEMPLATE(BM_Gaussian, Matrix<double>)
    ->Args({50})
    ->Args({100})
    ->Args({200})
    ->Args({300})
    ->Args({500})
    ->Args({700})
    ->Args({1000})
    ->Unit(benchmark::kMillisecond);

BENCHMARK_TEMPLATE(BM_Gaussian, JaggedMatrix<double>)
    ->Args({50})
    ->Args({100})
    ->Args({200})
    ->Args({300})
    ->Args({500})
    ->Args({700})
    ->Args({1000})
    ->Unit(benchmark::kMillisecond);

BENCHMARK_TEMPLATE(BM_Bareiss, Matrix<long long>)
    ->Args({50})
    ->Args({100})
    ->Args({200})
    ->Args({300})
    ->Args({500})
    ->Args({700})
    ->Args({1000})
    ->Unit(benchmark::kMillisecond);

BENCHMARK_TEMPLATE(BM_Bareiss, JaggedMatrix<long long>)
    ->Args({50})
    ->Args({100})
    ->Args({200})
    ->Args({300})
    ->Args({500})
    ->Args({700})
    ->Args({1000})
    ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();