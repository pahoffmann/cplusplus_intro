#include "stdlib.h"

///generator function object for std::generator function
class Aufgabe2_1{
public:
	int operator()(){
		return (rand()+1) % 100 +1 ;
	}
};