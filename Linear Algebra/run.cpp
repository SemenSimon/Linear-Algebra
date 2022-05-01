#include "allheaders.h"
#include <iostream>

int main() {
	Matrix A = Matrix({ {1,1,1},
						{2,1,0},
						{1,2,5} });

	double x[2][2] = { {1,2},
					   {3,4} };

	double* p = &(x[0][0]);

	Matrix B = Matrix(p,sizeof(x)/sizeof(x[0]),sizeof(x[0])/sizeof(x[0][0]));

	Matrix I = Matrix::id(2);

	std::cout << (A.inv()*A).to_string();
}