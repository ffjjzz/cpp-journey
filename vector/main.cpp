#include "vector/vector.h"
#include <vector>
#include <iostream>
#include <chrono>

//using MyVector = std::vector<int>;
using MyVector = vector<int>;

int main() {
	int N = 200'000'000;
	while (true){
		MyVector a;
		a.reserve(N);

		auto start = std::chrono::steady_clock::now(); 

		for (int i = 0; i < N; ++i){
			a.push_back(i);

		}

		auto end = std::chrono::steady_clock::now();

		std::chrono::duration<double> elapsed = end - start;
              	std::cout << "Время выполнения: " << elapsed.count() << " секунд\n";
	}
	return 0;
}

