/**************************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-10-23    
    Last modified date:		2013-10-24
    Description: "translating" c++ code to c
***************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "ccode.h"


#define CHECK_MALLOC(X)		if(!(X)) { fprintf(stderr, "malloc failed, line %d\n", __LINE__); return -1; }


/*######################################################################*/
/*						GLOBAL VARIABLES								*/
/*######################################################################*/

/* virtual tables */
extern Func vtblShape[];
extern Func vtblCircle[];
extern Func vtblSquare[];

extern int Shape_NShapes;


/*######################################################################*/
/*								FUNCTIONS								*/
/*######################################################################*/


void f1(Shape *_shape)
{
	( (void(*)(Shape*)) ( (*( *((Func**)_shape) + 1 ) )) ) (_shape);	/* draw */
}
/************************************************************************/

void f2(void)
{
	Shape_PrintNShapes();
}
/************************************************************************/

void f3(Circle* _cTemp)
{
	Circle_Draw_this(_cTemp);	/* draw */
	Circle_DTOR(_cTemp);		/* DTOR */
}
/************************************************************************/



/*######################################################################*/
/*									MAIN								*/
/*######################################################################*/
int main()
{
	Shape *array[3], arr2[3];
	Circle c, c2, arr3[4], cTemp1, cTemp2;
	Square *arr4, sqTemp;
	char *curr, *end;
	int i;
	
	Init();

	/* create c & call f3 */
	Circle_CTOR(&c);
	Circle_CCTOR(&cTemp1, &c);
	f3(&cTemp1);
	
	/* array: allocate */
	array[0] = (Shape*)malloc(sizeof(Circle));
	CHECK_MALLOC(array[0]);
	Circle_CTOR( (Circle*)array[0] );
	
	array[1] = (Shape*)malloc(sizeof(Square));
	CHECK_MALLOC(array[1]);
	Square_CTOR( (Square*)array[1] );
	
	array[2] = (Shape*)malloc(sizeof(Circle));
	CHECK_MALLOC(array[2]);
	Circle_CTOR( (Circle*)array[2] );
	
	/* array: draw */
	for(i=0; i<3; ++i)
	{
		( (void(*)(Circle*)) (*( *((Func**)array[i]) + 1 )) ) (array[i]);
	}
	
	/* array: delete */
	for(i=0; i<3; ++i)
	{
		( **( (ShapeDtor**) array[i]) ) (array[i]);
		free(array[i]);
	}
	
	/* arr2: create */
	Circle_CTOR( &cTemp2 );					/* create temporary */
	Shape_CCTOR(&arr2[0], &cTemp2 ); 		/* copy to arr2[0] (only shape part) */
	( **( (ShapeDtor**)&cTemp2 ) ) (&cTemp2);	/* destroy temporary */
	arr2[0].m_vtbl = vtblShape;				/* return vtbl pointer to shape vtbl */
		
	Square_CTOR( &sqTemp );					/* create temporary */
	Shape_CCTOR(&arr2[1], &sqTemp );		/* copy to arr2[1] (only shape part) */
	( **( (ShapeDtor**)&sqTemp ) ) (&sqTemp);	/* destroy temporary */
	arr2[1].m_vtbl = vtblShape;				/* return vtbl pointer to shape vtbl */
	
	Shape_CTOR( &arr2[2] );					/* create arr2[2] */
	
	/* arr2: draw */
	for(i=0; i<3; ++i)
	{	/* arr2 is known to be "Shape", so no need to go through VTable */
		Shape_Draw_this(&arr2[i]);	
	}
	
	Shape_PrintNShapes();
	
	/* create c2 */
	Circle_CTOR(&c2);
	Shape_PrintNShapes();
	
	/* arr3: create */
	for(i=0; i<4; ++i)
	{
		Circle_CTOR(&arr3[i]);
	}
	
	/* arr4: allocate & ctor */
	arr4 = 1 + (size_t*)malloc( sizeof(size_t) + 4*sizeof(Square) );
	CHECK_MALLOC(arr4);
	*((size_t*)arr4 - 1) = 4*sizeof(Square);
		
	for(i=0; i<4; ++i)
	{
		Square_CTOR(&arr4[i]);
	}
	
	/* arr4: delete */
	curr = (char*)arr4;
	end = curr + *((size_t*)arr4 - 1);
	
	while( curr < end )
	{
		curr += ( **( (ShapeDtor**)curr ) ) (curr);
	}
	assert( curr == end );
	free( (size_t*)arr4 - 1 );
	
	
	/*** DTORS for remaining objects ***/
	
	/* arr3 */
	for(i=3; i>=0; --i)
	{
		( *( (ShapeDtor*)arr3[i].m_shape.m_vtbl ) ) (&arr3[i]);
	}
	
	/* c2 */
	( *( (ShapeDtor*)c2.m_shape.m_vtbl ) ) (&c2);
	
	/* arr2 */
	for(i=2; i>=0; --i)
	{
		( *( (ShapeDtor*)arr2[i].m_vtbl ) ) (&arr2[i]);
	}
	
	/* c */
	( *( (ShapeDtor*)c.m_shape.m_vtbl ) ) (&c);
	
	return 0;
}
/*######################################################################*/


