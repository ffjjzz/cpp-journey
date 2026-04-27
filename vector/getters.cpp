#include<iostream>
#include "vector/vector.h"

int main(){
	vector<int> v = {1,2,3,4,5,6,7,8,9};
	v.show();


	std::cout << v[4] << std::endl;

	std::cout << v.at(4) << std::endl;



}
