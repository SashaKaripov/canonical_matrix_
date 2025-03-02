#include "functions.h"
#include "eigen/Eigen/Sparse"

int main()
{
	// Открываем файл с матрицей
	std::ifstream file("matrix_data.txt");
	int H_rows{5};
	int H_cols{15};
	std::vector<int> vector_messgae_bits{ 1,1,0,1,0,0,0,0,1,1 };
	Eigen::SparseMatrix<GF2> G_matrix{}, X_vector{};
	std::tie(G_matrix, X_vector) = H_to_X(file, vector_messgae_bits, H_rows, H_cols);
	std::cout << "G --------> " << G_matrix << std::endl;
	Eigen::SparseMatrix<GF2> zero_vector = checking_syndrome(X_vector, file, H_rows, H_cols);
	std::cout << "X --------> " << X_vector << std::endl;
	std::cout << "Zero_vector -------> " << zero_vector << std::endl;
	return 0;
}