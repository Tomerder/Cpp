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

class Circle : public Shape {
		friend class Shape;
public:
	~Circle() 		{ cout << "Circle::~Circle\n"; }
 	void draw() 	{ cout << "Circle::draw\n"; }
 	void erase() 	{ cout << "Circle::erase\n"; }
private:
	Circle() {} 
};

class Square : public Shape {
	friend class Shape;
public:
   	~Square() 	{ cout << "Square::~Square\n"; }
 	void draw() 	{ cout << "Square::draw\n"; }
  	void erase() 	{ cout << "Square::erase\n"; }
private:
	Square() {}
};

Shape* Shape::factory(const string& type) {
     Shape* ptrShape = 0;
  	if (type == "Circle")   
		ptrShape = new Circle;
  	if (type == "Square") 
		ptrShape = new Square;
	return ptrShape;
}

char* shp[]={ "Circle", "Square", "Circle",  ""};
int main() {
  	vector<Shape*> vShp;
	for(char** cp = shp; **cp; cp++) {		
		vShp.push_back(Shape::factory(*cp));
	}
	 for(int i = 0; i < vShp.size(); i++) {
    		 vShp[i]->draw();
    		 vShp[i]->erase();
  	}
} 
