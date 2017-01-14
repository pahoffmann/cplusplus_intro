/*
 * Traits.cpp
 *
 *  Created on: Jan 8, 2017
 *      Author: Thomas Wiemann (twiemann@uos.de)
 */

#include <iostream>

/// A struct to represent a vertex position
template<typename T>
struct GVertex
{
	GVertex(T x, T y, T z) : m_x(x), m_y(y), m_z(z) {}

	virtual void f(){};

	T m_x;	// x coordinate
	T m_y;	// y coordinate
	T m_z;	// z coordinate
};

/// A struct to represent a vertex with color
/// values
template<typename T, typename C>
struct CVertex : public GVertex<T>
{
	CVertex(T x, T y, T z, C r, C g, C b)
		: GVertex<T>(x,y,z), m_r(r), m_g(g), m_b(b) {}

	C m_r;	// red color component
	C m_g;	// green color component
	C m_b;	// blue color component
};

/// Some typedefs to use the templates above
typedef GVertex<float> Vertex;
typedef CVertex<float, unsigned int> ColorVertex;

/// A general traits class for vertices
template<typename VertexT>
struct VertexTraits
{
	static const bool HasColor = false;
};


/// A specialization for colored vertices
template<>
struct VertexTraits<ColorVertex>
{
	static const bool HasColor = true;
};


template<typename T>
void print_vertex(T& vertex)
{
	std::cout << vertex.m_x << " " << vertex.m_y << " " << vertex.m_z << std::endl;
	std::cout << "COLOR?" << std::endl;


	if(VertexTraits<T>::HasColor){
		std::cout << "YES!" <<std::endl;
		int r = (dynamic_cast<ColorVertex&>(vertex)).m_r;
		int g = (dynamic_cast<ColorVertex&>(vertex)).m_g;
		int b = (dynamic_cast<ColorVertex&>(vertex)).m_b;
		
		std::cout << r << " " << g << " " << b << std::endl;
		 
	} else std::cout << "NO!" << std::endl;
	
}

/*template <>
void print_vertex(ColorVertex& vertex){
	std::cout << "COLOR" << std::endl;
	std::cout << vertex.m_x << " " << vertex.m_y << " " << vertex.m_z << std::endl;
	std::cout << vertex.m_r << " " << vertex.m_g << " " << vertex.m_b << std::endl;
}*/

int main(int argc, char** argv)
{
	// Declare to different kinds of vertex
	ColorVertex cv(1.0, 2.0, 3.0, 255, 0, 120);
	Vertex v(2.0, 2.0, 3.0);

	// Print information
	print_vertex(cv);
	print_vertex(v);

	return 0;
}




