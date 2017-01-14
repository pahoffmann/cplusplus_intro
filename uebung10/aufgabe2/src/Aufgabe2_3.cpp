#include <functional>

///adder struct for adding with for_each - loop
class Aufgabe2_3 : public std::unary_function<int, void> {

public:
	int sum;
	Aufgabe2_3() : sum(0) { }
	void operator()(int x) { sum += x; }
};