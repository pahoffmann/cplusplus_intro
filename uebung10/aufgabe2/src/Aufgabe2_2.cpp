#include <string>
#include <stdlib.h>

///Random-String-Generator-Function-Object
class Aufgabe2_2{
public:
	std::string operator()(){
		
		int size = 5 + ((rand()+1) % 6 );
		std::string str;
		for(int i = 0; i < size; i++){
			str+=(char)('a' + rand()%26);
		}
		
		return str;
	}
};