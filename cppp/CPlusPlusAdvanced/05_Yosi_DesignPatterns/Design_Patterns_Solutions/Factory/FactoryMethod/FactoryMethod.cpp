#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Shape {
public:
	virtual 		~Shape() {}
  	virtual void 	draw() = 0;
  	virtual void 	erase() = 0;

  	static Shape* factory(const string& type);

};

// CIRCLE
// note: private CTOR
class Circle : public Shape
{
	friend class Shape;
public:
	~Circle() 		{ cout << "Circle::~Circle\n"; }
 	void draw() 	{ cout << "Circle::draw\n"; }
 	void erase() 	{ cout << "Circle::erase\n"; }
private:
	Circle() {} 
};

// SQUARE
class Square : public Shape
{
	friend class Shape;
public:
   	~Square() 	{ cout << "Square::~Square\n"; }
 	void draw() 	{ cout << "Square::draw\n"; }
  	void erase() 	{ cout << "Square::erase\n"; }
private:
	Square() {}
};

// FACTORY function
// returns ptr to base
// create shape according to requested type
// if no known type - returns NULL
// needs to include circle.h, square.h
// accepted practice: put impl. of factory in a cpp ond put includes only there
Shape* Shape::factory(const string& type) {
     Shape* ptrShape = 0;
  	if (type == "Circle")   
		ptrShape = new Circle;
  	if (type == "Square") 
		ptrShape = new Square;
	return ptrShape;
}

// usually: additional function Destroy, receiving ptr to shape, when vactor
// is a data member
// can decide that receiving e.g. NULL means "delete everything"


// hard-coded - just for example
char* shp[]={ "Circle", "Square", "Circle",  ""};

// example
// note: no need for includes: circle.h, square.h
int main()
{
  	vector<Shape*> vShp;
	for(char** cp = shp; **cp; cp++) {		
		vShp.push_back(Shape::factory(*cp));
	}
	 for(int i = 0; i < vShp.size(); i++) {
    		 vShp[i]->draw();
    		 vShp[i]->erase();
  	}
} 
