#include <iostream>
#include <vector>
int main() {
	int a[2][3] = {{1,3,5},{7,8,9}};
	int *p;
	p = *a;
	std::vector<std::vector<int>> v;
	for(int i = 0; i < 2; i++) {
		std::vector<int> x;
		for (int j = i*3; j < (i+1)*3; j++) {
			x.push_back( *(p+j) );
		}
	v.push_back(x);
	} 
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << v[i][j];
			std::cout << " ";
		}
		std::cout << "\n";
	}
	 int b[2] = {1,2};
	 int c[2] = {1,1};
	 int g[2] = b + c;

	 std::cout << g[0];
};

