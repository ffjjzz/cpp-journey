#include<iostream>
#include "vector/vector.h"

int main(){
	vector<int> v = {1,2,3,4,5,6,7,8,9};
	v.show();


	for (auto start = v.begin(); start != v.end(); ++start){
		std::cout << *start << std::endl;
	}



}

