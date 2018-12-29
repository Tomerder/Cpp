#include <string>
#include <vector>
#include <iostream>
using namespace std;

class ShapeFactory;

class Shape {
public:
	virtual 		~Shape() {}
  	virtual void 	draw() = 0;
  	virtual void 	erase() = 0;
};

class Circle : public Shape {
		friend class ShapeFactory;
public:
	~Circle() 		{ cout << "Circle::~Circle\n"; }
 	void draw() 	{ cout << "Circle::draw\n"; }
 	void erase() 	{ cout << "Circle::erase\n"; }
private:
	Circle() {} 
};

class Square : public Shape {
	friend class ShapeFactory;
public:
   	~Square() 	{ cout << "Square::~Square\n"; }
 	void draw() 	{ cout << "Square::draw\n"; }
  	void erase() 	{ cout << "Square::erase\n"; }
private:
	Square() {}
};


class ShapeFactory {
public:
	static Shape* Create(const string& type, int color) {
		Shape* ptrShape = 0;
		if (type == "Circle")   {
			ptrShape = new Circle;
			noc++;
		}
  		if (type == "Square") 
			ptrShape = new Square;
		return ptrShape;
	}
private:
	ShapeFactory();
	ShapeFactory(const ShapeFactory&);
	ShapeFactory& operator=(const ShapeFactory&);
};


char* shp[]={ "Circle", "Square", "Circle",  ""};
int main() {
  	vector<Shape*> vShp;
	for(char** cp = shp; **cp; cp++) {		
		vShp.push_back(ShapeFactory::Create(*cp));
	}
	 for(int i = 0; i < vShp.size(); i++) {
    		 vShp[i]->draw();
    		 vShp[i]->erase();
  	}
} 
