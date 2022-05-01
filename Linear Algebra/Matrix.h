#pragma once
#include <vector>
#include <string>
/*
* Immutable class representing an (mxn)-matrix.
*/
class Matrix
{
private:
	int rows;
	int cols;
	std::vector<std::vector<double>> arr;

public:
	Matrix(double* p, int m, int n);
	Matrix(std::vector<std::vector<double>> x);

	Matrix operator + (Matrix const& obj);
	Matrix operator - (Matrix const& obj);
	Matrix operator * (Matrix const& obj);
	Matrix operator * (double const& c);
	
	static Matrix id(int n);
	static Matrix zero(int m, int n);
	static Matrix unit(int x, int y, int m, int n);

	int get_rows() { return rows; }
	int get_cols() { return rows; }
	std::vector<std::vector<double>> get_arr() { return arr; }
	std::vector<double> operator[] (int const& index) { return arr[index]; }

	Matrix row(int i);
	Matrix col(int i);
	Matrix t();
	Matrix submatrix(int m, int n);
	Matrix inv();

	std::string to_string();

};