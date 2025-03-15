#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include "eigen/Eigen/Sparse"
#include "eigen/Eigen/Dense"
#include "GF2.hpp"
#include <typeinfo>
#include <utility>
#include <filesystem>


Eigen::SparseMatrix<GF2> read_matrix(const std::string& file_name, const int& H_rows, const int& H_cols)
{
    // Проверяем, существует ли файл
    if (!std::filesystem::exists(file_name)) {
        throw std::runtime_error("File does not exist");
    }

    std::ifstream file(file_name);

    file.clear();
    file.seekg(0);
    
    std::string line;
    Eigen::SparseMatrix<GF2> H(H_rows, H_cols);
    int H_col{};

    // Извлекаем матрицу H из файла
    for (int i{}; i < H_rows; i++) {
        H_col = 0;
        std::getline(file, line);
        std::istringstream iss(line);
        int number;
        while (iss >> number) {
            H.insert(i, H_col) = GF2(number);
            H_col += 1;
        }
    }

    return H;
}


void gaussJordanGF2(Eigen::Matrix<GF2, Eigen::Dynamic, Eigen::Dynamic>& mat) {
    int rows = mat.rows();
    int cols = mat.cols();
    int lead = 0;

    for (int r = 0; r < rows; ++r) {
        if (lead >= cols)
            return;

        int i = r;
        while (mat(i, lead) == GF2(0)) {
            ++i;
            if (i == rows) {
                i = r;
                ++lead;
                if (lead == cols)
                    return;
            }
        }

        // Меняем строки местами
        mat.row(i).swap(mat.row(r));

        // Обнуляем элементы в текущем столбце
        for (int i = 0; i < rows; ++i) {
            if (i != r && mat(i, lead) == GF2(1)) {
                mat.row(i) += mat.row(r);  // В GF₂ сложение эквивалентно XOR
            }
        }

        ++lead;
    }
}

Eigen::SparseMatrix<GF2> f(const std::string& file_matrix_H, const int& H_rows, const int& H_cols)
{
    // Читаем из файла матрицу H
    Eigen::SparseMatrix<GF2> H {read_matrix(file_matrix_H, H_rows, H_cols)};

    Eigen::Matrix<GF2, Eigen::Dynamic, Eigen::Dynamic> dense_H = H.toDense();

    // Копируем правую и левую часть матрицы H
    Eigen::Matrix<GF2, Eigen::Dynamic, Eigen::Dynamic> right_H = dense_H.block(0, H_cols - H_rows, H_rows, H_rows);
    Eigen::Matrix<GF2, Eigen::Dynamic, Eigen::Dynamic> left_H = dense_H.block(0, 0, H_rows, H_cols - H_rows);

    // Создаем единичную матрицу для проверок
    Eigen::Matrix<GF2, Eigen::Dynamic, Eigen::Dynamic> identity_matrix(H_rows, H_rows);
    identity_matrix.setIdentity(); // Заполняем единицами

    // Проверяем, нужно ли преобразовывать матрицу или нет
    if (identity_matrix != right_H)
    {


        Eigen::Matrix<GF2, Eigen::Dynamic, Eigen::Dynamic> dense_H_switched(H_rows, H_cols);

        // Меняем местами правую и левую часть
        dense_H_switched.block(0, H_rows, H_rows, H_cols - H_rows) = left_H;
        dense_H_switched.block(0, 0, H_rows, H_rows) = right_H;

        gaussJordanGF2(dense_H_switched);

        Eigen::Matrix<GF2, Eigen::Dynamic, Eigen::Dynamic> check_identity_matrix = dense_H_switched.block(0, 0, H_rows, H_rows);

        // Проверяем, слева единичная матрица или нет
        if (identity_matrix != check_identity_matrix)
        {
            throw std::runtime_error("isnt identity matrix");
        }

        // Копируем правую и левую часть матрицы H_switched после Гаусса-Джардана
        Eigen::Matrix<GF2, Eigen::Dynamic, Eigen::Dynamic> left_dense_H_switched = dense_H_switched.block(0, 0, H_rows, H_rows);
        Eigen::Matrix<GF2, Eigen::Dynamic, Eigen::Dynamic> right_dense_H_switched = dense_H_switched.block(0, H_rows, H_rows, H_cols - H_rows);

        Eigen::Matrix<GF2, Eigen::Dynamic, Eigen::Dynamic> H_result(H_rows, H_cols);
        H_result.block(0, 0, H_rows, H_cols - H_rows) = right_dense_H_switched;
        H_result.block(0, H_cols - H_rows, H_rows, H_rows) = left_dense_H_switched;

        Eigen::SparseMatrix<GF2> H_res = H_result.sparseView();

        return H_res;
    }
    else{
        return H;
    }
}

#endif FUNCTIONS_H