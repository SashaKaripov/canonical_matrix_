#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "external/doctest/doctest.h"
#include "functions.h"


TEST_CASE("Checking the correctness of the formation of the G_matrix and the encoded message"){
    std::ifstream test_file("test_data.txt");
	int G_lines{10};
	int G_rows{15};
    std::string line;
	Eigen::SparseMatrix<GF2> test_G(G_lines, G_rows);
	int test_G_row{};
	for (int i{}; i < G_lines; i++) {
		test_G_row = 0;
		std::getline(test_file, line);
		std::istringstream iss(line);
		int number;
		while (iss >> number) {
			test_G.insert(i, test_G_row) = GF2(number);
			test_G_row += 1;
		}
	}
    std::ifstream file("matrix_data.txt");
	int H_lines{5};
	int H_rows{15};
	std::vector<int> vector_messgae_bits{ 1,1,0,1,0,0,0,0,1,1 };
	Eigen::SparseMatrix<GF2> G_matrix{}, X_vector{};
    std::tie(G_matrix, X_vector) = H_to_X(file, vector_messgae_bits, H_lines, H_rows);
    bool cheking_1 = true;
    for (int i = 0; i < G_lines; ++i) {
        for (int j = 0; j < G_rows; ++j) {
            if (test_G.coeff(i, j) != G_matrix.coeff(i, j)){
                cheking_1 = false;
                break;
            }
        if (cheking_1 == false){
            break;
        }
        }   
    }
    CHECK(cheking_1);
}

TEST_CASE("Checking the size of the matrices and the sindrom"){
    std::ifstream file("matrix_data.txt");
	int H_rows{5};
	int H_cols{15};
	std::vector<int> vector_messgae_bits{ 1,1,0,1,0,0,0,0,1,1 };
	Eigen::SparseMatrix<GF2> G_matrix{}, X_vector{};
	std::tie(G_matrix, X_vector) = H_to_X(file, vector_messgae_bits, H_rows, H_cols);
	Eigen::SparseMatrix<GF2> zero_vector = checking_syndrome(X_vector, file, H_rows, H_cols);

    CHECK(G_matrix.cols() == H_cols);
    CHECK(G_matrix.rows() == H_cols - H_rows);
    CHECK(X_vector.rows() == 1);
    CHECK(X_vector.cols() == H_cols);

    bool cheking_2 = true;
    for (int i = 0; i < H_rows; ++i) {
        if (zero_vector.coeff(0, i) != 0){
            cheking_2 = false;
            break;
        } 
    }
    CHECK(cheking_2);
}