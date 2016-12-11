#include "SparseVector.hpp"
#include <iostream>

int main(void){
	SparseVector s(10);
	//for(int i=1;i<5;i++){
	
	//	s.setNonzeroElem(i,i*2);

	//}
	std::cout<<s.getSize()<<std::endl;
	SparseVector *x = new SparseVector(s);
	std::cout<<x->getSize()<<std::endl;
	SparseVector test(10);
	test = s;
	std::cout<<test.getSize()<<std::endl;
	//s.io();
	//test.io();
	//x->io();
	return 0;
}
