#include "determinant/Gaussian.hpp"
#include "matrix/Matrix.hpp"

#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <utility>

double gaussian(const Matrix<double>& matrix){
    Matrix<double> a(matrix);
    const size_t n = a.rows();

    double determinant = 1.0;
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
        if (a(pivotRow, k) == 0.0){
            return 0.0;
        }

        //swap rows
        if (pivotRow != k){
            for (size_t j = 0; j < n; ++j){
                std::swap(a(k, j), a(pivotRow, j));
            }
            sign = -sign;
        }

        const double pivot = a(k, k);
        determinant *= pivot;

        //eliminate elements below the pivot
        for (size_t i = k + 1; i < n; ++i){
            const double factor = a(i, k) / pivot;
            a(i, k) = 0.0;
            for (size_t j = k + 1; j < n; ++j){
                a(i, j) -= factor * a(k, j);
            }
        }
    }
    return sign * determinant;
}