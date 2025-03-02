#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include "eigen/Eigen/Sparse"
#include "GF2.hpp"
#include <typeinfo>
#include <utility>

std::pair<Eigen::SparseMatrix<GF2>, Eigen::SparseMatrix<GF2>> H_to_X(std::ifstream& file_matrix_H, std::vector<int> bits_message, int H_rows, int H_cols)
{
    std::string line;
    Eigen::SparseMatrix<GF2> H(H_rows, H_cols);
    int H_col{};
    // Извлекаем матрицу H из файла
    for (int i{}; i < H_rows; i++) {
        H_col = 0;
        std::getline(file_matrix_H, line);
        std::istringstream iss(line);
        int number;
        while (iss >> number) {
            H.insert(i, H_col) = GF2(number);
            H_col += 1;
        }
    }
    Eigen::SparseMatrix<GF2> H_transposed = H.transpose();
    int G_cols{ H_cols };
    int G_rows{ H_cols - H_rows };
    Eigen::SparseMatrix<GF2> G_matrix(G_rows, G_cols);
    // Добавляем в G слева единичную матрицу
    for (int row{}; row < G_rows; row++) {
        for (int col{}; col < G_rows; col++) {
            if (row == col) {
                G_matrix.insert(row, col) = GF2(1);
            }
            else {
                G_matrix.insert(row, col) = GF2(0);
            }
        }
    }
    // Добавляем в G справа транспонированную матрицу A
    for (int row{}; row < (H_cols - H_rows); row++) {
        for (int col{}; col < H_rows; col++) {
            GF2 A_element{ H_transposed.coeff(row, col) };
            G_matrix.insert(row, col + G_rows) = A_element;
        }
    }
    Eigen::SparseMatrix<GF2> message_vector(1, G_rows);
    for (int col{}; col < G_rows; col++){
        GF2 bit_message{bits_message[col]};
        message_vector.insert(0, col) = bit_message;
    }
    Eigen::SparseMatrix<GF2> X = message_vector * G_matrix;
    return std::make_pair(G_matrix, X);
}

Eigen::SparseMatrix<GF2> checking_syndrome(Eigen::SparseMatrix<GF2>& X, std::ifstream& file_matrix_H, int H_rows, int H_cols)
{
    std::string line;
    Eigen::SparseMatrix<GF2> H(H_rows, H_cols);
    int H_col{};
    for (int i{}; i < H_rows; i++) {
        H_col = 0;
        std::getline(file_matrix_H, line);
        std::istringstream iss(line);
        int number;
        while (iss >> number) {
            H.insert(i, H_col) = GF2(number);
            H_col += 1;
        }
    }
    Eigen::SparseMatrix<GF2> H_transposed = H.transpose();
    // Делаем проверку. X*HT=0
    Eigen::SparseMatrix<GF2> zero_vector = X * H_transposed;
    return zero_vector;
}
#endif FUNCTIONS_H