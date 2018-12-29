/**************************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-10-23
    Last modified date:		2013-10-24
    Description: header file for "translating" c++ code to c
***************************************************************************************/

#ifndef __CCODE_H__
#define __CCODE_H__


typedef void(*Func)();

typedef struct Shape_t
{
	Func*	m_vtbl;
	int 	m_id;
} Shape;


typedef struct Circle_t
{
	Shape 	m_shape;
	int 	m_radius;
} Circle;


typedef struct Square_t
{
	Shape 	m_shape;
} Square;


typedef int(*ShapeDtor)(Shape*);

/************************************************************************/

void	Init(void);	/* initialize "static" data members */

void 	Shape_CTOR			(Shape* _shape);
void 	Shape_CCTOR			(Shape* _shape, const Shape* const _other);
int 	Shape_DTOR			(Shape* _shape);
void	Shape_Draw_this		(Shape* _shape);

void 	Circle_CTOR			(Circle* _circle);
void 	Circle_CCTOR		(Circle* _circle, const Circle* const _other);
int 	Circle_DTOR			(Circle* _circle);
void	Circle_Draw_this	(Circle* _circle);
void	Circle_Radius_this	(Circle* _circle);

void 	Square_CTOR			(Square* _square);
void 	Square_CCTOR		(Square* _square, const Square* const _other);
int 	Square_DTOR			(Square* _square);
void	Square_Draw_this	(Square* _square);

void	Shape_PrintNShapes(void);


#endif /* __CCODE_H__ */
