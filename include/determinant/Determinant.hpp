#pragma once

template<typename T>
class Matrix;

template<typename T>
class JaggedMatrix;

long long determinant(const Matrix<long long>& matrix);
long long determinant(const JaggedMatrix<long long>& matrix);

double determinant(const Matrix<double>& matrix);
double determinant(const JaggedMatrix<double>& matrix);