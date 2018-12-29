/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-00-00    
    Last modified date:		2013-00-00
    Description: 	
****************************************************************************/

#include <iostream>
using namespace std;

#include "Polygon.h"


void Foo(CPolygon& _poly)
{
	CRectangle *rec = static_cast<CRectangle*>(&_poly);
	rec->SetColor("Black");
}
/*######################################################################*/

//void Foo(const CPolygon& _poly)
//{
//	CRectangle *rec = const_cast<CRectangle*>(&_poly);
//	rec->SetColor("Black");
//}
/*######################################################################*/

//void Foo(const CPolygon& _poly)
//{
//	const CRectangle *rec = reinterpret_cast<const CRectangle*>(&_poly);
//	rec->SetColor("Black");
//}
/*######################################################################*/



int main()
{
	CRectangle myRec(3,4,"white");
	
	cout << "rectangle color: " << myRec.GetColor() << endl;
	
	Foo(myRec);
	
	cout << "rectangle color: " << myRec.GetColor() << endl;
	
	return 0;
}

/*######################################################################*/




