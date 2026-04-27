#include<iostream>
#include "vector/vector.h"

int main(){
	vector<int> v;
	v.show();


	vector<int> v2{std::allocator<int>()};
	v2.show();


	vector<int> v3(6, 2);
	v3.show();

	vector<int> v4{1,2,3,4,5};
	v4.show();

	vector<int> v5(v4);
	v5.show();

	vector<int> v6(std::move(v5));
	v6.show();
	
	vector<int> v7 = v4;
	v7.show();

	vector<int> v8 = std::move(v4);
	v8.show();

	vector<int> v9 = {1,2,3,4,5,6,7};
	v9.show();



}
