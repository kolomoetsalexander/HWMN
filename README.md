# HWMN — Matrix

A C++ assignment focused on RAII, dynamic memory management, move semantics, and determinant computation for generic square matrices.

## Objectives

- RAII and the Rule of Five.
- Implement deep copying and move semantics.
- Compare two memory layouts: contiguous storage (`T*`) and jagged arrays (`T**`).
- Implement determinant algorithms without modifying the original matrix.
- Benchmark different algorithms and memory layouts.

## Algorithms

- **Gaussian Elimination** — determinant computation for floating-point matrices using partial pivoting.
- **Bareiss Algorithm** — determinant computation for integer matrices.

## Structure

```text
HWMN/
├── include/
│   ├── matrix/
│   │   ├── Matrix.hpp
│   │   └── JaggedMatrix.hpp
│   └── determinant/
│       ├── Gaussian.hpp
│       ├── Bareiss.hpp
│       └── Determinant.hpp
├── src/
│   └── main.cpp
├── tests/
├── benchmarks/
├── CMakeLists.txt
└── README.md
```

## Technologies

- C++17
- CMake
- GoogleTest

## Testing

Unit tests, end-to-end tests, and benchmarks to evaluate correctness and performance across different matrix sizes.

## Constraints

Matrix storage must be implemented manually using dynamic arrays, without STL containers.