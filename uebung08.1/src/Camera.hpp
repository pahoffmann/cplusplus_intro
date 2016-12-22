#include <SDL2/SDL.h>
#include <iostream>
#include "Pixel.hpp"
/***
* A camera representation to scroll within a level
*/
class Camera
{
private:
  jumper::Pixel p;
public:


	/***
	* Constructs a camera with the given pixel offsets
	*/
	Camera(int x=0 , int y=0 );

        
        void move(const jumper::Pixel &offset);  
        

	/// Returns the current x-position
	int x();



	/// Returns the current y-position
	int y();


	/// Destructor
	virtual ~Camera();

private:


	/// X-Position of the camera
	int m_x;


	/// Y-Position of the camera
	int m_y;

};
