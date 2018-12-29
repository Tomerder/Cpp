#include <string>
#include <iostream>
#include <vector>

using namespace std;
//-------------------------------------------------------------------

class Shape_t;
typedef vector<Shape_t*>	vShapes_t;

class Shape_t
{
public:
	virtual Shape_t* clone() = 0;	// pure virtual CLONE
	static vShapes_t	m_shapes;
};

vShapes_t	Shape_t::m_shapes;	// init static data-member

//-------------------------------------------------------------------

class Circle_t : public Shape_t
{
public:
	
	// impl. of clone - calling copy CTOR
	virtual Shape_t* clone()   { 
		cout << "Circle_t::clone" << endl; 
		Shape_t* ptr = new Circle_t(*this); // copying *this
		m_shapes.push_back(ptr);	// push into vector for convenience
		return ptr; 
	}

};

//-------------------------------------------------------------------

class Square_t : public Shape_t
{
public:

	// impl. of clone - calling copy CTOR
	virtual Shape_t* clone() { 
		cout << "Square_t::clone" << endl; 
		Shape_t* ptr = new Square_t(*this);
		m_shapes.push_back(ptr);
		return ptr; 
	}

};

//-------------------------------------------------------------------

Circle_t	c;
Square_t	s;

int main() {
	

	Shape_t*	cp = c.clone();	// new circle as a copy of 1st
	Shape_t*	sp = s.clone(); //  "  square ---- " ------


	Shape_t* ptrVecShape_t = Shape_t::m_shapes[1]->clone();

	return 0;
}
