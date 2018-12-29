#include <iostream>
#include <vector>
#include <map>

using namespace std;

#define		ID_LINE1	0
#define		ID_LINE2	1
#define		ID_LINE3	2
#define		ID_RCTANGL	3
#define		ID_PICTURE	4

// --------------------------------------------------------------------- //

class Shape {
public:
	virtual			~Shape(){};
					Shape()	{}
	virtual void	Add(unsigned int id)	{}
	virtual void	Remove(unsigned int id)	{};
	
	//leaf classes will not override it..however, it will be overridden by the composite class.
	virtual Shape*	GetChild(unsigned int id) { throw 0; return 0;};
	virtual Shape*	GetParent()			{ return Parent;};
	virtual void	SetParent(Shape* s)	{ Parent = s;}
	virtual void	Display()	{};
	virtual Shape*	FindItem(unsigned int id); 

protected:	
	Shape*	Parent;
	int		resource_id;
};
// --------------------------------------------------------------------- //

typedef map < int, Shape*, less< int> > shapeContainer;

shapeContainer Container;
shapeContainer::iterator it;

Shape* Shape::FindItem(unsigned int id) {
	Shape* s = 0;
	it = Container.find(id);
	if (it != Container.end()) {
		s = (*it).second;
	}

	return s;
}

// --------------------------------------------------------------------- //
class Point : public Shape {
public:
	virtual		~Point(){}
				Point():x(0),y(0)	{}
				Point(int x, int y):x(x), y(y)	{}
				Point(const Point& p) {
					x = p.x;	y = p.y;
				}
				Point& operator = (const Point& p) {
					x = p.x;	y = p.y;
					return *this;
				}

	virtual		void Display() {
		cout<<"Coordinates are (X,Y) :"<<x<<" " <<y<<endl;
	}

	int xCoord() { return x;}
	int yCoord() { return y;}
private:
	int x;
	int y;
};
// --------------------------------------------------------------------- //


//class Line is working as a leaf class.
class Line : public Shape {
public:
	virtual ~Line(){}
	virtual void Display() {
		cout<<"Begining point is:";
		begin.Display();
		cout<<"End Point is:";
		end.Display();
		cout << endl;
	}
	static Line* CreateLine(unsigned int id, Point a, Point b) {
		return new Line(id,a,b);
	}

private:
	Line(unsigned int id):begin(0,0),end(0,0) {
		resource_id = id;
		Container.insert(shapeContainer::value_type(resource_id,(Shape*)this));
	}
	
	Line(unsigned int id, Point a, Point b):begin(a),end(b) {
		resource_id = id;
		Container.insert(shapeContainer::value_type(resource_id,(Shape*)this));
	}
	
private:
	Point begin;
	Point end;
};
// --------------------------------------------------------------------- //

//this will work as another leaf class. 
class Rectangle : public Shape {
public:
	static Rectangle* CreateRectange(unsigned int id, Point& p, int width, int height) {
		return new Rectangle(id, p, width, height);
	}

	virtual ~Rectangle(){}
	virtual void Display() {
		cout<<"The four vertices are:"<<endl << endl;;
		cout<<"Top Left :" ;	top_left.Display();
		cout <<"Top Right :";	top_right.Display();	
		cout<<"Bottom Left :";	bottom_left.Display();
		cout<<"Bottom Right :"; bottom_right.Display();
		cout << endl;
	}

private:
	Rectangle(unsigned int id, Point& p, int width, int height) {
		top_left = p;
		top_right = Point(p.xCoord() + width, p.yCoord());
		bottom_left = Point(p.xCoord() , p.yCoord() + height); 
		bottom_right = Point(p.xCoord() + width, p.yCoord() + height);
		resource_id = id;
		Container.insert(shapeContainer::value_type(resource_id,(Shape*)this));

	}
	
	Point top_left;
	Point top_right;
	Point bottom_left;
	Point bottom_right;
};
// --------------------------------------------------------------------- //

//this will work as a composite class
class Picture : public Shape {
public:
	virtual ~Picture() {
		vector<Shape*>::iterator p = Components.begin();
		
		int pos = 0;
		while (p != Components.end()) {
			delete(Components.at(pos));
			p++;
			pos++;
		}
		Components.clear();
	}
	Picture(unsigned int id) {
		resource_id = id;
		Container.insert(shapeContainer::value_type(resource_id,(Shape*)this));
	}
	virtual void Display() {
		vector<Shape*>::iterator p = Components.begin();
		while (p != Components.end()) {
			(*p)->Display();
			p++;
		}
	}

	//Adds the component with the resource id equal to the passed parameter
	virtual void Add (unsigned int id) {
		Shape* s = FindItem(id);
		Components.push_back(s);
		s->SetParent(this);
	}
	
	//removes the  component from the list with the resource_id equal to the parameter passed
	virtual void Remove(unsigned int id) {
		Shape* s = FindItem(id);
		vector<Shape*>::iterator p = Components.begin();
		int pos = 0;
		while (p != Components.end()) {
			if(Components.at(pos) == s) break;
			pos++;
			p++;
		}
		Components.erase(p);
		s->SetParent(NULL);
	}
	
	//will return the chile having the id equal to the passed value.
	virtual Shape* GetChild (unsigned int id) {
		return FindItem(id);
	}

private:
	vector<Shape*> Components;
};

// --------------------------------------------------------------------- //
// --------------------------------------------------------------------- //
int main() {
	Point p1(10,20);
	Point p2(30,40);
	Point p3(50,60);
	Point p4(70,80);
	Point p5(100,110);
	Point p6(150,200);

	Line* l1 = Line::CreateLine(ID_LINE1,p1,p2);
	Line* l2 = Line::CreateLine(ID_LINE2,p3,p4);
	Line* l3 = Line::CreateLine(ID_LINE3,p5,p6);
	
	Rectangle* r1 = Rectangle::CreateRectangle(ID_RCTANGL, p1, 50,25);

	Shape* p = new Picture(ID_PICTURE);
	p->Add(ID_LINE1);
	p->Add(ID_LINE2);
	p->Add(ID_LINE3);
	p->Add(ID_RCTANGL);
	
	(p->GetChild(ID_RCTANGL))->Display();		// display Rectange

	p->Remove(ID_RCTANGL);						// remove Rectange from picture
	p->Display();								
		
	delete p;
	return 0;
}
// --------------------------------------------------------------------- //

/*

The four vertices are:

Top Left :		Coordinates are (X,Y) :10 20
Top Right :		Coordinates are (X,Y) :60 20
Bottom Left :	Coordinates are (X,Y) :10 45
Bottom Right :	Coordinates are (X,Y) :60 45

Begining point is:	Coordinates are (X,Y) :10 20
End Point is:		Coordinates are (X,Y) :30 40

Begining point is:	Coordinates are (X,Y) :50 60
End Point is:		Coordinates are (X,Y) :70 80

Begining point is:	Coordinates are (X,Y) :100 110
End Point is:		Coordinates are (X,Y) :150 200

*/

