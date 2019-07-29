#include <iostream>
#include <cstdlib>
int n = 500000;
int main() {
	std::cout << n << "\n";
	for (int i = 0; i < n; ++i) 
		std::cout << rand() % 20000000 + 2 << "\n";
}
