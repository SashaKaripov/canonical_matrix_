#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "external/doctest/doctest.h"
#include "functions.h"
#include <string>


TEST_CASE("Checking exception when file does not exist"){
    CHECK_THROWS_WITH(f("non_existent_file.txt", 5, 13), "File does not exist");
}

TEST_CASE("Checking exception when matrix isnt identity"){
    CHECK_THROWS_WITH(f("bad_matrix_data.txt", 5, 13), "isnt identity matrix");
}

TEST_CASE("SimpleMatrix"){
    Eigen::Matrix<GF2, Eigen::Dynamic, Eigen::Dynamic> mat(3, 3);
    mat << GF2(1), GF2(1), GF2(1),
           GF2(0), GF2(1), GF2(0),
           GF2(0), GF2(0), GF2(1);

    gaussJordanGF2(mat);

    Eigen::Matrix<GF2, Eigen::Dynamic, Eigen::Dynamic> expected(3, 3);
    expected << GF2(1), GF2(0), GF2(0),
                GF2(0), GF2(1), GF2(0),
                GF2(0), GF2(0), GF2(1);

    CHECK(mat == expected);
}

TEST_CASE("ZeroMatrix") {
    Eigen::Matrix<GF2, Eigen::Dynamic, Eigen::Dynamic> mat(3, 3);
    mat << GF2(0), GF2(0), GF2(0),
           GF2(0), GF2(0), GF2(0),
           GF2(0), GF2(0), GF2(0);

    gaussJordanGF2(mat);

    Eigen::Matrix<GF2, Eigen::Dynamic, Eigen::Dynamic> expected(3, 3);
    expected << GF2(0), GF2(0), GF2(0),
                GF2(0), GF2(0), GF2(0),
                GF2(0), GF2(0), GF2(0);

    CHECK(mat == expected);
}

TEST_CASE("RectangularMatrix") {
    Eigen::Matrix<GF2, Eigen::Dynamic, Eigen::Dynamic> mat(3, 4);
    mat << GF2(1), GF2(1), GF2(1), GF2(0),
           GF2(0), GF2(0), GF2(1), GF2(0),
           GF2(0), GF2(1), GF2(0), GF2(0);

    gaussJordanGF2(mat);

    Eigen::Matrix<GF2, Eigen::Dynamic, Eigen::Dynamic> expected(3, 4);
    expected << GF2(1), GF2(0), GF2(0), GF2(0),
                GF2(0), GF2(1), GF2(0), GF2(0),
                GF2(0), GF2(0), GF2(1), GF2(0);

    CHECK(mat == expected);
}

TEST_CASE("AlreadyInRungsForm") {
    Eigen::Matrix<GF2, Eigen::Dynamic, Eigen::Dynamic> mat(3, 3);
    mat << GF2(1), GF2(0), GF2(0),
           GF2(0), GF2(1), GF2(0),
           GF2(0), GF2(0), GF2(1);

    gaussJordanGF2(mat);

    Eigen::Matrix<GF2, Eigen::Dynamic, Eigen::Dynamic> expected(3, 3);
    expected << GF2(1), GF2(0), GF2(0),
                GF2(0), GF2(1), GF2(0),
                GF2(0), GF2(0), GF2(1);

    CHECK(mat == expected);
}

TEST_CASE("Checking the correct matrix"){
    Eigen::SparseMatrix<GF2> matrix {read_matrix("test_data.txt", 5, 13)};
    std::string H_file("matrix_data.txt");

    int H_rows{5};
    int H_cols{13};

    Eigen::SparseMatrix<GF2> res = f(H_file, H_rows, H_cols);

    bool checking_1 = true;
    for (int i = 0; i < H_rows; ++i) {
        for (int j = 0; j < H_cols; ++j) {
            if (res.coeff(i, j) != matrix.coeff(i, j)){
                checking_1 = false;
                break;
            }
        if (checking_1 == false){
            break;
        }
        }   
    }
    CHECK(checking_1);
}