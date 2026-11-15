#pragma once
#include <chrono>
#include <stdexcept>

template<typename Function>
double benchmark(Function function, int repetitions = 5){
    if (repetitions <= 0){
        throw std::invalid_argument("invalid repetitions");
    }

    double totalTime = 0.0;
    volatile long double result = 0;

    for(int i = 0; i < repetitions; ++i){
        auto start = std::chrono::steady_clock::now();
        result = static_cast<long double>(function());
        auto end = std::chrono::steady_clock::now();
        double elapsed = std::chrono::duration<double, std::milli>(end - start).count();
        totalTime += elapsed;
    }
    return totalTime / repetitions;
}
