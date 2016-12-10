#include <iostream>
class Pixel{

	int x;
	int y;

public :
	
	Pixel(int x=0, int y=0);

	
	Pixel&  operator+=(const Pixel &p);
	
	
	Pixel& operator=(const Pixel &p);
	

	

	int getX() const;
	int getY() const;
	void setX(int x);
	void setY(int y);
	~Pixel();


};

std::ostream& operator<<(std::ostream &out, const Pixel &p) ;

Pixel operator+(Pixel ret,const Pixel &p) ;

bool operator==(const Pixel &p,const Pixel &other) ;
	
bool operator!=(const Pixel &p, const Pixel &other) ;
