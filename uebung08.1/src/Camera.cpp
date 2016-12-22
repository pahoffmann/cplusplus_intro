#include "Camera.hpp"

Camera::Camera(int x, int y){
        jumper::Pixel p1(x,y);
	p=p1;
}


void Camera::move(const jumper::Pixel &offset){
  p+=offset;
}

int Camera::x(){
  return p.x();
}

int Camera::y(){
  return p.y();
}

Camera::~Camera(){

}
