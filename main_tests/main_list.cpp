#include"../bits/list.h"
#include"iostream"
#include<chrono>
#include<list>


using lst = list<int>;
//using lst = std::list<int>;


int main(){
	int N = 50'000'000;
	
	while (true){
		auto start = std::chrono::steady_clock::now();	
		lst list;
	
		for (int i = 0;i < N; ++i){
			list.push_front(i);
		}

		auto end = std::chrono::steady_clock::now();

		std::chrono::duration<double> elapsed = end - start;

		std::cout<< elapsed << std::endl;
	

	}
}

