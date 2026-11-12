add_library(hwmn
    src/determinant/Gaussian.cpp
    src/determinant/Bareiss.cpp
    src/determinant/Determinant.cpp
)

target_include_directories(hwmn PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(HWMN
    src/main.cpp
)

target_link_libraries(HWMN PRIVATE hwmn)