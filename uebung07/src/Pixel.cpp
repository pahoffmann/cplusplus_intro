#include "Pixel.hpp"

Pixel::Pixel(int x, int y){
	this->x = x;
	this->y = y;
}	


Pixel& Pixel::operator+=(const Pixel &p){
	this->x+=p.getX();
	this->y+=p.getY();

	return *this;
}

Pixel operator+(Pixel ret, const Pixel &p) {
	ret+=p;
	
	return ret;
}


Pixel& Pixel::operator=(const Pixel &p){
	if(this != &p){
		this->x = p.getX();
		this->y = p.getY();
	}

	return *this;
	
}

std::ostream& operator<<(std::ostream& out, const Pixel &p) 
{
   return out << p.getX() << '|' << p.getY() ;
}

bool operator==(const Pixel &p,const Pixel &other)  {
	return(other.getX()==p.getX() && other.getY() == p.getY());
}

bool operator!=(const Pixel &p,const Pixel &other) {
	return !(p==other);
}

void Pixel::setX(int x)  {
	this->x = x;
}
void Pixel::setY(int y)  {
	this->y = y;
}

int Pixel::getX() const{
	return this->x;
}

int Pixel::getY() const {
	return this->y;
}

Pixel::~Pixel(){

}




	


