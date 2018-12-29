#include <string>
#include <iostream>
#include <vector>

using namespace std;
//-------------------------------------------------------------------

class Shape_t;
typedef vector<Shape_t*>	vShapes_t;

class Shape_t {
public:
	virtual Shape_t* clone() = 0;
	static vShapes_t	m_shapes;
};

vShapes_t	Shape_t::m_shapes;	// init static data-member

//-------------------------------------------------------------------

class Circle_t : public Shape_t {
public:

	virtual Shape_t* clone()   { 
		cout << "Circle_t::clone" << endl; 
		Shape_t* ptr = new Circle_t(*this);
		m_shapes.push_back(ptr);
		return ptr; 
	}

};

//-------------------------------------------------------------------

class Square_t : public Shape_t {
public:
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
	

	Shape_t*	cp = c.clone();
	Shape_t*	sp = s.clone();


	Shape_t* ptrVecShape_t = Shape_t::m_shapes[1]->clone();

	return 0;
}
