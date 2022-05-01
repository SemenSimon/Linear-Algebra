#include <iostream>
#include <assert.h>
#include <cassert>
#include "MatrixUtils.h"

/*
* Function: Computes determinant of matrix via laplacian expansion.
*/
double det(Matrix A) {
	assert(A.get_rows() == A.get_cols());
	int size = A.get_rows();

	if (size == 2) { return A[0][0]*A[1][1] - A[1][0]*A[0][1]; }

	double value = 0;
	for (int i = 0; i < size; i++) {
		value += pow(-1,i) * (A[0][i] * det(A.submatrix(0, i)));
	}

	return value;
}

Matrix adj(Matrix A) {
	assert(A.get_rows() == A.get_cols());
	int size = A.get_rows();

	std::vector<std::vector<double>> cofactor(size, std::vector<double>(size));

	int c = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cofactor[i][j] = pow(-1,c) * det(A.submatrix(i, j));
			c++;
		}
	}
	return Matrix(cofactor).t();


}
