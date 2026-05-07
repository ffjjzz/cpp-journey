#include"../bits/vector.h"
#include"iostream"
#include<chrono>


using vct = vector<int>;
//using vct = std::vector<int>;


int main(){
	int N = 100'000'000;
	
	while (true){
		auto start = std::chrono::steady_clock::now();	
		vct vec;
		vec.reserve(N);
	
		for (int i = 0;i < N; ++i){
			vec.push_back(i);
		}

		auto end = std::chrono::steady_clock::now();

		std::chrono::duration<double> elapsed = end - start;

		std::cout<< elapsed << std::endl;
	

	}
}
