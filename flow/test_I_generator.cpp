#include <cstdlib>
#include <iostream>
#include <vector>

int main() {
	size_t n;
	std::cin >> n;
	std::vector<std::vector<char>> g(n, std::vector<char> (n, '#'));
	std::vector<size_t> points(n, 0);

	for (size_t i = 0; i < n; ++i) {
		for (size_t j = i + 1; j < n; ++j) {
			size_t r = rand();
			if (r % 4 == 0) {
				g[i][j] = 'W';
				g[j][i] = 'L';
				points[i] += 3;
				points[j] += 0;
			} else if (r % 4 == 1) {
				 g[i][j] = 'w';
                         	 g[j][i] = 'l';
				 points[i] += 2;
                                points[j] += 1;
			} else if (r % 4 == 2 ) {
				 g[i][j] = 'L';
                                g[j][i] = 'W';
				points[i] += 0;
                                points[j] += 3;
			} else if (r % 4 ==3 ) {
				g[i][j] = 'l';
	                        g[j][i] = 'w';
				points[i] += 1;
                                points[j] += 2;
			}

		}
	}

	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < n; ++j) 
			std::cout << g[i][j];
		std::cout << "\n";
	}

	std::cout << "\n";

	for (auto p: points) 
		std::cout << p << " ";

	std::cout << "\n\n";


	 for (size_t i = 0; i < n; ++i) {
                for (size_t j = i + 1; j < n; ++j) {
			if (rand() % 3 == 1) {
				g[i][j] = '.';
				g[j][i] = '.';
			}
		}
	 }
				

	  for (size_t i = 0; i < n; ++i) {
                for (size_t j = 0; j < n; ++j) {
			if (i == j) std::cout << "#";
			else                        std::cout <<g[i][j];
		}
                std::cout << "\n";
        }
	
	  return 0;

	}


