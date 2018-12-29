#include <iostream>
using namespace std;

/*######################################################################*/
class Shape
{
public:
    Shape()
		: m_id(++NShapes)
		{
			cout << "Shape::Ctor()" << endl;
		}

    virtual ~Shape(){ --NShapes; cout << "Shape::Dtor()" << endl; }

    Shape(const Shape &other)
		: m_id(++NShapes)
		{
			cout << "Shape::CCtor()" << endl;
		}

    virtual void Draw()
		{
			cout << "Shape::Draw() : " << m_id << endl;
		}

    static void PrintNShapes() { cout << "NShapes: " << NShapes << endl;}

private:
    static int NShapes;
    int m_id;
    Shape &operator=(const Shape &); // disabled
};
/*######################################################################*/

int Shape::NShapes = 0;

/*######################################################################*/
class Circle: public Shape
{
public:
    Circle()
		: m_radius(2)
		{
			cout << "Circle::Ctor()" << endl;
		}
    Circle(const Circle &other )
		: Shape(other),
		  m_radius(other.m_radius)
		{
			cout << "Circle::CCtor()" << endl;
		}
    ~Circle() { cout << "Circle::Dtor()" << endl; }
    void Draw() { cout << "Circle::Draw()" << endl; }
    virtual void Radius() { cout << "Circle::Radius()" << endl; }

private:
    int m_radius;
};
/*######################################################################*/

class Square: public Shape
{
public:
    Square() { cout << "Square::Ctor()" << endl; }
    Square(const Square &other ): Shape(other) { cout << "Square::CCtor()" << endl; }
    ~Square() { cout << "Square::Dtor()" << endl; }
    void Draw() { cout << "Square::Draw()" << endl; }

private:
};
/*######################################################################*/

void f1(Shape &s) { s.Draw(); }
void f2() { Shape::PrintNShapes(); }

void f3(Circle c) { c.Draw(); }


/*######################################################################*/
int main(int argc, char **argv, char **envp)
{
    Circle c;
    f3(c);

    Shape *array[] =
	{
		new Circle(),
		new Square(),
		new Circle()
	};

    for(int i = 0; i < 3; ++i) array[i]->Draw();
    for(int i = 0; i < 3; ++i) delete array[i];

    Shape arr2[] =
	{
		Circle(),
		Square(),
		Shape()
	};

    for(int i = 0; i < 3; ++i) arr2[i].Draw();

    Shape::PrintNShapes();
    Circle c2;
    c2.PrintNShapes();
   
    Circle arr3[4];
    Square *arr4 = new Square[4];
    delete [] arr4;

    return 0;
} 
/*######################################################################*/
