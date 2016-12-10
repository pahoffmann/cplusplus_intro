#include "SparseVector.hpp"
#include <iostream>

int main(void){
	SparseVector s(10);
	//std::cout<<s.start->index<<std::endl;
	std::cout<<s.getSize()<<std::endl;
	//SparseVector x(s);
	SparseVector test(10);
	test = s;
	std::cout<<test.getSize()<<std::endl;
	
	return 0;
}
