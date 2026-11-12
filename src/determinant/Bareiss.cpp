#include "include/determinant/Bareiss.hpp"
#include "include/matrix/Matrix.hpp"

#include <cstddef>
#include <limits>
#include <stdexcept>
#include <utility>

long long bareiss(const Matrix<long long>& matrix){
    Matrix<long long> a(matrix);
    const size_t n = a.rows();

    //previous leading element
    long long previousPivot = 1;
    //sing of determinant
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
            //if first row's leading el is 0, we need to change row, if all - 0, - end
            sign = -sign;
        }

        const long long pivot = a(k, k);

        //Bareiss formula
        for (size_t i = k + 1; i < n; i++){
            for (size_t j = k + 1; j < n; j++){

                const int numerator = pivot * a(i, j) - a(i, k) * a(k, j);
                const long long value = numerator / previousPivot;
                a(i, j) = value;
            }
            a(i, k) = 0;
        }

        
        previousPivot = pivot;
    }
    const int result = sign * a(n - 1, n - 1);

    return static_cast<long long>(result);
}