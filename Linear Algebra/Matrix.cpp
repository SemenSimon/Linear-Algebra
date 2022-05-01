#include "Matrix.h"
#include "MatrixUtils.h"
#include <iostream>
#include <string>
#include <assert.h>
#include <cassert>

/* 
* Constructor: Initializes matrix from a pointer to an (mxn) two
	dimensional array.
*
* *p: pointer to array
*  m: row dimension
*  n: column dimension
* 
*/
Matrix::Matrix(double *p, int m, int n) {
	rows = m;
	cols = n;
	//std::vector<std::vector<double>> mat;

	for (int i = 0; i < m; i++) {
		std::vector<double> x;
		for (int j = i*n; j < (i + 1)*n; j++) {
			x.push_back(*(p + j));
		}
		arr.push_back(x);
	}
}

/*
* Constructor: Initializes matrix from two dimensional vector.
*/
Matrix::Matrix(std::vector<std::vector<double>> x) {
	rows = x.size();
	cols = x[0].size();
	arr = x;

}

/*
* Override: addition operator.
*/
Matrix Matrix::operator + (Matrix const& other) {
	assert(rows == other.rows && cols == other.cols);

	std::vector<std::vector<double>> temp = arr;

	for (int i = 0; i < rows; i++) {
		std::vector<double>* p = &temp[i];
		for (int j = 0; j < cols; j++) {
			double* f = &((*p)[0]);
			*(f + j) += other.arr[i][j];
		}
	}
	return Matrix(temp);
}

/*
* Override: subtraction operator.
*/
Matrix Matrix::operator - (Matrix const& other) {
	assert(rows == other.rows && cols == other.cols);

	std::vector<std::vector<double>> temp = arr;

	for (int i = 0; i < rows; i++) {
		std::vector<double>* p = &temp[i];
		for (int j = 0; j < cols; j++) {
			double* f = &((*p)[0]);
			*(f + j) -= other.arr[i][j];
		}
	}
	return Matrix(temp);

}

/*
* Override: multiplication operator for scalars.
*/
Matrix Matrix::operator * (double const& c) {
	std::vector<std::vector<double>> temp = arr;

	for (int i = 0; i < rows; i++) {
		std::vector<double>* p = &temp[i];
		for (int j = 0; j < cols; j++) {
			double* f = &((*p)[0]);
			*(f + j) *= c;
		}
	}
	return Matrix(temp);
}

/*
* Override: multiplication operator for matrices.
*/
Matrix Matrix::operator * (Matrix const& other) {
	assert(cols == other.rows);

	std::vector<std::vector<double>> temp(rows,std::vector<double>(other.cols));

	for (int j = 0; j < other.cols; j++) {
		for (int i = 0; i < rows; i++) {
			for (int k = 0; k < cols; k++) {
				temp[i][j] += arr[i][k]*other.arr[k][j];
			}
		}
	}

	return Matrix(temp);
}



std::string Matrix::to_string() {
	std::string str;
	for (std::vector<double> v : arr) {
		for (double x : v) {
			str += std::to_string((int)x) + " ";
		}
		str += "\n";
	}
	return str;
}

/*
* Function: Returns zero matrix of specified size.
*/
Matrix Matrix::zero(int m, int n) {
	std::vector<std::vector<double>> mat;

	for (int i = 0; i < m; i++) {
		std::vector<double> row;
		for (int j = 0; j < n; j++) {
			row.push_back(0);
		}
		mat.push_back(row);
	}
	return Matrix(mat);
}

/*
* Function: Returns identity matrix of specified size.
*/
Matrix Matrix::id(int n) {
	std::vector<std::vector<double>> mat;

	for (int i = 0; i < n; i++) {
		std::vector<double> row;
		for (int j = 0; j < n; j++) {
			if (i == j) {
				row.push_back(1);
			}
			else {
				row.push_back(0);
			}		
		}
		mat.push_back(row);
	}
	return Matrix(mat);
}

/*
* Function: Returns matrix of specified size with 1 in a single entry.
*/
Matrix Matrix::unit(int x, int y, int m, int n) {
	std::vector<std::vector<double>> mat;

	for (int i = 0; i < m; i++) {
		std::vector<double> row;
		for (int j = 0; j < n; j++) {
			if (i == x && j == y) {
				row.push_back(1);
			}
			else {
				row.push_back(0);
			}
		}
		mat.push_back(row);
	}
	return Matrix(mat);
}

/*
* Function: Returns (1xn)-matrix of i-th row.
*/
Matrix Matrix::row(int i) {
	return Matrix({arr[i]});
}

/*
* Function: Returns (mx1)-matrix of j-th column.
*/
Matrix Matrix::col(int j) {
	std::vector<std::vector<double>> mat(rows, std::vector<double>(1));
	for (int i = 0; i < rows; i++) {
		mat[i][0] = arr[i][j];
	}
	return Matrix(mat);
}

/*
* Function: Returns transpose of matrix.
*/
Matrix Matrix::t() {
	std::vector<std::vector<double>> mat;

	for (int i = 0; i < cols; i++) {
		std::vector<double> row;
		for (int j = 0; j < rows; j++) {
			row.push_back(arr[j][i]);
		}
		mat.push_back(row);
	}
	return Matrix(mat);
}

/*
* Function: Returns submatrix with m-th row and n-th column removed.
*/
Matrix Matrix::submatrix(int m, int n) {
	assert(m >= 0 && n >= 0 && m <= rows && n <= cols);

	std::vector<std::vector<double>> temp(rows - 1, std::vector<double>(cols - 1));

	int x = 0; 
	for (int i = 0; i < rows; i++) {
		if (i != m) {
			int y = 0;
			for (int j = 0; j < cols; j++) {
				if (j != n) {					
					temp[x][y] = arr[i][j];
					y++;
				}
			}
			x++;
		}
	}
	return Matrix(temp);
}

Matrix Matrix::inv() {
	Matrix A = Matrix(arr);
	assert(det(A) != 0);
	return adj(A) * (1 / det(A));
}


