#include "include/determinant/Bareiss.hpp"
#include "include/matrix/Matrix.hpp"

#include <cstddef>
#include <limits>
#include <stdexcept>
#include <utility>

long long bareiss(const Matrix<long long>& matrix){
    Matrix<long long> a(matrix);
    const size_t n = a.rows();

    if (n != a.cols()){
        throw std::invalid_argument("matrix must be square");
    }

    if (n == 0){
        throw std::invalid_argument("matrix cant be empty");
    }
    long long previousPivot = 1;
    int sign = 1;

    for (size_t k = 0; k + 1 < n; k++){

        //find leading element
        size_t pivotRow = k;

        while (pivotRow < n && a(pivotRow, k) == 0){
            ++pivotRow;
        }
        if (pivotRow == n){
            return 0;
        }
        //rows swap
        if (pivotRow != k){
            for (size_t j = 0; j < n; j++){
                std::swap(a(k, j), a(pivotRow, j));
            }
            sign = -sign;
        }

        const long long pivot = a(k, k);

        //Bareiss formula
        for (size_t i = k + 1; i < n; i++){
            for (size_t j = k + 1; j < n; j++){

                const __int128 numerator = static_cast<__int128>(pivot) * a(i, j) - static_cast<__int128>(a(i, k)) * a(k, j);

                if (numerator % previousPivot != 0){
                    throw std::runtime_error("Non-exact division");
                }
                const __int128 value = numerator / previousPivot;

                if (value < std::numeric_limits<long long>::min() || value > std::numeric_limits<long long>::max()){
                    throw std::overflow_error("Matrix element overflow");
                }
                a(i, j) = static_cast<long long>(value);
            }
            a(i, k) = 0;
        }
        previousPivot = pivot;
    }
    const __int128 result = static_cast<__int128>(sign) * a(n - 1, n - 1);

    if (result < std::numeric_limits<long long>::min() || result > std::numeric_limits<long long>::max()){
        throw std::overflow_error("Determinant overflow");
    }
    return static_cast<long long>(result);
}