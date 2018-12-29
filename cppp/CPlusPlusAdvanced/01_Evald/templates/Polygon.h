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
  protected:
    int width, height;
    
  public:
    void set_values (int a, int b)
    	{ width=a; height=b; }
    virtual int area ()
		{ return (0); }
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
