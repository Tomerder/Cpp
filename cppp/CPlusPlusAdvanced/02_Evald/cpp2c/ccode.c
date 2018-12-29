/**************************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-10-23    
    Last modified date:		2013-10-24
    Description: "translating" c++ code to c
***************************************************************************************/

#include <stdio.h>

#include "ccode.h"


/*######################################################################*/
/*						GLOBAL VARIABLES								*/
/*######################################################################*/

/* virtual tables */
Func vtblShape[]  = { (ShapeDtor*)Shape_DTOR,	(void(*)(Shape*))Shape_Draw_this };
Func vtblCircle[] = { (ShapeDtor*)Circle_DTOR,	(void(*)(Circle*))Circle_Draw_this, (void(*)(Circle*))Circle_Radius_this };
Func vtblSquare[] = { (ShapeDtor*)Square_DTOR,	(void(*)(Square*))Square_Draw_this };

int Shape_NShapes;



/*######################################################################*/
/*								FUNCTIONS								*/
/*######################################################################*/

void	Init(void)
{
	Shape_NShapes = 0;
}
/************************************************************************/

void Shape_PrintNShapes(void)
{
	printf("NShapes: %d\n", Shape_NShapes);
}
/************************************************************************/


/************************************************************************/
/*								SHAPE									*/
/************************************************************************/

void 	Shape_CTOR	(Shape* _shape)
{
	_shape->m_vtbl = vtblShape;
	_shape->m_id = ++Shape_NShapes;
	printf("Shape::Ctor()\n");
}
/************************************************************************/

void 	Shape_CCTOR	(Shape* _shape, const Shape* const _other)
{
	_shape->m_id = ++Shape_NShapes;
	_shape->m_vtbl = vtblShape;
	printf("Shape::CCtor()\n");
}
/************************************************************************/

int 	Shape_DTOR	(Shape* _shape)
{
	--Shape_NShapes;
	printf("Shape::Dtor()\n");
	return sizeof(Shape);
}
/************************************************************************/

void	Shape_Draw_this	(Shape* _shape)
{
	printf("Shape::Draw() : %d\n", _shape->m_id);
}
/************************************************************************/


/************************************************************************/
/*								CIRCLE									*/
/************************************************************************/

void 	Circle_CTOR		(Circle* _circle)
{
	Shape_CTOR(_circle);
	_circle->m_radius = 2;
	_circle->m_shape.m_vtbl = vtblCircle;
	printf("Circle::Ctor()\n");
}
/************************************************************************/

void 	Circle_CCTOR	(Circle* _circle, const Circle* const _other)
{
	Shape_CCTOR(_circle, _other);
	_circle->m_radius = _other->m_radius;
	_circle->m_shape.m_vtbl = vtblCircle;
	printf("Circle::CCtor()\n");
}
/************************************************************************/

int 	Circle_DTOR		(Circle* _circle)
{
	printf("Circle::Dtor()\n");
	_circle->m_shape.m_vtbl = vtblShape;
	
	( **( (ShapeDtor**) _circle)) (_circle);
	return sizeof(Circle);
}
/************************************************************************/

void	Circle_Draw_this		(Circle* _circle)
{
	printf("Circle::Draw()\n");
}
/************************************************************************/

void	Circle_Radius_this	(Circle* _circle)
{
	printf("Circle::Radius()\n");
}
/************************************************************************/


/************************************************************************/
/*								SQUARE									*/
/************************************************************************/

void 	Square_CTOR		(Square* _square)
{
	Shape_CTOR(_square);
	_square->m_shape.m_vtbl = vtblSquare;
	printf("Square::Ctor()\n");
}
/************************************************************************/

void 	Square_CCTOR	(Square* _square, const Square* const _other)
{
	Shape_CCTOR(_square, _other);
	_square->m_shape.m_vtbl = vtblSquare;
	printf("Square::CCtor()\n");
}
/************************************************************************/

int 	Square_DTOR		(Square* _square)
{
	printf("Square::Dtor()\n");
	_square->m_shape.m_vtbl = vtblShape;
	
	( **( (ShapeDtor**) _square)) (_square);
	return sizeof(Square);
}
/************************************************************************/

void	Square_Draw_this		(Square* _square)
{
	printf("Square::Draw()\n");
}
/************************************************************************/


