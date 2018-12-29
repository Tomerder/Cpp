/***************************************************************************
    Author:
    Creation date:  		2013-00-00    
    Last modified date:		2013-00-00
    Description: 	
****************************************************************************/

#ifndef __POLYGON_H__
#define __POLYGON_H__

#include <string>

class CPolygon
{
  protected:
    int width, height;
    
  public:
    
    CPolygon(int a, int b)
    	{ set_values(a,b); }
    void set_values (int a, int b)
    	{ width=a; height=b; }
    virtual int area ()
		{ return (0); }
};
/*######################################################################*/


class CRectangle: public CPolygon
{
  public:
    
    CRectangle(int a, int b, const char* color) : CPolygon::CPolygon(a,b)
    	{ SetColor(color); }
    	
    int area ()
	{ return (width * height); }
  
	void 		SetColor(const char* _color)	{ color = _color; }
	std::string GetColor() const				{ return color; }
	
  private:
	std::string color;
};
/*######################################################################*/


class CTriangle: public CPolygon
{
  public:
    CTriangle(int a, int b, const char* color) : CPolygon::CPolygon(a,b)
    	{ SetColor(color); }
    	
    int area ()
      { return (width * height / 2); }
	
	void 		SetColor(const char* _color)	{ color = _color; }
	std::string GetColor() const 				{ return color; }
	
  private:
	std::string color;
};
/*######################################################################*/



#endif  /* __POLYGON_H__ */
