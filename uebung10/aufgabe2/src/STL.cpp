/*
 * Main.cpp
 *
 *  Created on: 12.01.2017
 *      Author: patrick
 */

#include <time.h>
#include <vector>
#include "stdlib.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <functional>
#include "Aufgabe2_1.cpp"
#include "Aufgabe2_2.cpp"
#include "Aufgabe2_3.cpp"





///Comp-Functor for sort-method
struct comp{
	bool operator()(const std::string& a, const std::string &b){
		return (a < b);
	}
};
///Main for doing stuff

int main(){
	int size = 100;

	///2.1 - vector<int>
	std::vector<int> values(size);
	srand(time(NULL));
	std::cout << "Randoms Integers [1,100]: " << std::endl;
	//ints i;
	std::generate(values.begin(),values.end(),Aufgabe2_1());
	std::copy(values.begin(),values.end(),std::ostream_iterator<int>(std::cout, ", "));
	std::cout << std::endl;
	std::cout << std::endl;
	//2.2 - vector<string>
	
	std::vector<std::string> strings(size);
	std::cout << "Random Sorted Strings [5,10]:" << std::endl;
	std::generate(strings.begin(),strings.end(),Aufgabe2_2());
	sort(strings.begin(),strings.end(),comp());
	std::copy(strings.begin(),strings.end(),std::ostream_iterator<std::string>(std::cout, ", "));
	std::cout << std::endl;
	std::cout << std::endl;

	//2.3 - unary function object
	Aufgabe2_3 sum = for_each(values.begin(),values.end(),Aufgabe2_3());
	std::cout << "Sum of Vector Elements: " << std::endl;
	std::cout << "The sum is : " << sum.sum << std::endl;



	return 0;

}
