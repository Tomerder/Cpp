#include <stdio.h>
#include <stdlib.h>

static int NShapes = 0;

typedef struct Shape Shape;
typedef void(*Func)();
struct Shape
{
	Func* m_vt;
	int m_id;
};

void Shape_Draw_this(Shape* _this);
void Shape_dtor(Shape* _this);

Func g_ShapeVT[] = {Shape_dtor, Shape_Draw_this};

void Shape_ctor(Shape* _this)
{
	_this->m_vt = g_ShapeVT;
	_this->m_id = ++NShapes;
	printf("Shape::Ctor()%d\n",_this->m_id);
}

void Shape_dtor(Shape* _this)
{
	--NShapes;
	printf("Shape::Dtor()%d\n",_this->m_id);
}

void Shape_copy_ctor(Shape* _this, Shape* _other)
{
	_this->m_vt = g_ShapeVT;
	_this->m_id = ++NShapes;
	printf("Shape::CCtor()%d\n",_this->m_id);
}

void Shape_Draw_this(Shape* _this)
{
	printf("Shape::Draw() : %d\n",_this->m_id);
}

static void PrintNShapes() { printf("NShapes: %d\n", NShapes);}

typedef struct Circle Circle;
struct Circle
{
	Shape m_papa;
	int m_radius;
};

void Circle_Draw_this(Circle* _this);
void Circle_dtor(Circle* _this);
void Circle_Radius_this(Circle* _this);

Func g_CircleVT[] = {(Func)Circle_dtor, (Func)Circle_Draw_this, (Func)Circle_Radius_this};

void Circle_ctor(Circle* _this)
{
	Shape_ctor((Shape*)_this);
	_this->m_radius = 2;
	*(Func**)_this = g_CircleVT;
	printf("Circle::Ctor()%d\n",((Shape*)_this)->m_id);
}

void Circle_copy_ctor(Circle* _this, Circle* _other)
{
	Shape_copy_ctor((Shape*)_this, (Shape*)_other);
	_this->m_radius = _other->m_radius;
	*(Func**)_this = g_CircleVT;
	printf("Circle::CCtor()%d\n",((Shape*)_this)->m_id);
}

void Circle_dtor(Circle* _this)
{
	printf("Circle::Dtor()%d\n",((Shape*)_this)->m_id);
	Shape_dtor((Shape*)_this);
}

void Circle_Draw_this(Circle* _this)
{
	printf("Circle::Draw()%d\n",((Shape*)_this)->m_id);
}

void Circle_Radius_this(Circle* _this)
{
	printf("Circle::Radius()%d\n",((Shape*)_this)->m_id);
}


typedef struct Square Square;
struct Square
{
	Shape m_papa;
};

void Square_Draw_this(Square* _this);
void Square_dtor(Square* _this);

Func g_SquareVT[] = {(Func)Square_dtor, (Func)Square_Draw_this};

void Square_ctor(Square* _this)
{
	Shape_ctor((Shape*)_this);
	*(Func**)_this = g_SquareVT;
	printf("Square::Ctor()%d\n",((Shape*)_this)->m_id);
}

void Square_copy_ctor(Square* _this, Square* _other)
{
	Shape_copy_ctor((Shape*)_this, (Shape*)_other);
	*(Func**)_this = g_SquareVT;
	printf("Square::CCtor()%d\n",((Shape*)_this)->m_id);
}

void Square_dtor(Square* _this)
{
	printf("Square::Dtor()%d\n",((Shape*)_this)->m_id);
	Shape_dtor((Shape*)_this);
}

void Square_Draw_this(Square* _this)
{
	printf("Square::Draw()%d\n",((Shape*)_this)->m_id);
}



/*---------------------------------------------------------------------*/
void f1(Shape *_shape)
{
	( (void(*)(Shape*)) ( (*( *((Func**)_shape) + 1 ) )) ) (_shape);
}
/*---------------------------------------------------------------------*/
void f2(void)
{
	PrintNShapes();
}
/*---------------------------------------------------------------------*/
void f3(Circle* _c)
{
	Circle_Draw_this(_c);
	Circle_dtor(_c);	/* because this should have been just a copy. */
}
/*---------------------------------------------------------------------*/


int main(int argc, char **argv, char **envp)
{
	int i;
	Circle c, cCopy, c2;
	Shape* array[3];

	/*arr2 and its temps*/
	Shape arr2[3];
	Circle circleTmp;
	Square squareTmp;

	/*arr3*/
	Circle arr3[4];

	/*arr4*/
	Square* arr4[4];

	Func* VT;

	/*This is like passing by value...*/
	Circle_ctor(&c);
	Circle_copy_ctor(&cCopy, &c);
	f3(&cCopy);

    array[0] = (Shape*)malloc(sizeof(Circle)); 
	array[1] = (Shape*)malloc(sizeof(Square));
	array[2] = (Shape*)malloc(sizeof(Circle));
	Circle_ctor((Circle*)array[0]);
	Square_ctor((Square*)array[1]);
	Circle_ctor((Circle*)array[2]);

	/* array: draw */
	for(i = 0; i < 3; ++i)
	{
		VT = *((Func**)array[i]);
		VT[1](array[i]);
	}

	/* array: delete */
	for(i = 0; i < 3; ++i)
	{		
		VT = *((Func**)array[i]);
		VT[0](array[i]);
	}

	/*Initialize arr2 of Shape*/
	Circle_ctor(&circleTmp);
	Shape_copy_ctor(&arr2[0], (Shape*)&circleTmp);
	Circle_dtor(&circleTmp);
	arr2[0].m_vt = g_ShapeVT;	/*Slicing!*/

	Square_ctor(&squareTmp);
	Shape_copy_ctor(&arr2[1], (Shape*)&squareTmp);
	Square_dtor(&squareTmp);
	arr2[1].m_vt = g_ShapeVT;	/*Slicing!*/

	Shape_ctor(&arr2[2]);

	/*Draw arr2 shapes*/
    for(i = 0; i < 3; ++i) 
	{
		Shape_Draw_this(&arr2[i]);
	}

	PrintNShapes();

	/*Ctor of c2*/
	Circle_ctor(&c2);
	PrintNShapes();
	
	/*ctors of arr3*/
    for(i = 0; i < 4; ++i) 
	{
		Circle_ctor(&arr3[i]);
	}

		/*Allocate memory and ctors of arr4*/
		for(i = 0; i < 4; ++i) 
		{
			arr4[i] = (Square*)malloc(sizeof(Square));
			Square_ctor(arr4[i]);
		}

		/*Destroy and free*/
		for(i = 3; i >= 0; --i) 
		{
			VT = *((Func**)arr4[i]);
			VT[0](arr4[i]);
			free(arr4[i]);
		}

	/*dtors of arr3*/
    for(i = 3; i >= 0; --i) 
	{
		Circle_dtor(&arr3[i]);
	}

	/*dtor of c2*/
	Circle_dtor(&c2);

	/*dtors of arr2*/
    for(i = 2; i >= 0; --i) 
	{
		Shape_dtor(&arr2[i]);
	}

	/*dtor of c*/
	Circle_dtor(&c);

	return 0;
} 
