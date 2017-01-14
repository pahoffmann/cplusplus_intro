#include <string>
#include <stdlib.h>

///Random-String-Generator-Function-Object
class Aufgabe2_2{
public:
	std::string operator()(){

		 char chars[] =
		 "0123456789"
		 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		 "abcdefghijklmnopqrstuvwxyz";
		
		int size = 5 + ((rand()+1) % 6 );
		std::string str;
		for(int i = 0; i < size; i++){
			str+=chars[(rand()+1) % (sizeof(chars)/sizeof(*chars))];
		}
		
		return str;
	}
};