#include <iostream>
#include "functions.h"


int main()
{
    std::string H_file("D:/canonical_matrix/matrix_data.txt");

    int H_rows{5};
    int H_cols{13};

    std::cout << f(H_file, H_rows, H_cols);
    
    return 0;
}