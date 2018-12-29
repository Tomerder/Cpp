/***************************************************************************
    Author:
    Creation date:  		2013-00-00    
    Last modified date:		2013-00-00
    Description: 	
****************************************************************************/

#ifndef __POLYGON_H__
#define __POLYGON_H__


class CPolygon
{
  public:
    
    explicit CPolygon(int a, int b) : width(a), height(b) {};
    explicit CPolygon (const CPolygon& _poly)
    	{ width = _poly.width; height = _poly.height; }
    
    void set_values (int a, int b)
    	{ width=a; height=b; }
    int get_width() { return width; }
    int get_height() { return height; }
    
    virtual int area ()
		{ return (0); }
		
  protected:
    int width, height;
    
};
/*######################################################################*/


class CRectangle: public CPolygon
{
  public:
    int area ()
	{ return (width * height); }
};
/*######################################################################*/


class CTriangle: public CPolygon
{
  public:
    int area ()
      { return (width * height / 2); }
};
/*######################################################################*/



#endif  /* __POLYGON_H__ */
