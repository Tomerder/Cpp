#include <iostream>
using namespace std;

// ===================================================================== //
// Example: draw a point on a (large) image
// ===================================================================== //

class Point {
public:
	Point(int x,int y) : x(x),y(y) {}
private:
	int x,y;
};
// --------------------------------------------------------------------- //
class Image {
  public:
	  virtual void Draw(const Point& p) { cout << "Point Draw" << endl;}
};
// --------------------------------------------------------------------- //

extern Image* LoadImageFile(const char*) { return new Image;}  
// --------------------------------------------------------------------- //
 
class ProxyImage {
public:
    ProxyImage(const char* imageFile) { // start with filename but not ptr (not loaded yet)
		    m_imageFile = imageFile;
			m_image = 0;
		}
    virtual ~ProxyImage() {}

    virtual Image* operator->() { return LoadImage();}
    virtual Image& operator*()  { return *LoadImage();}

	void	checkPassword() {}	// protection proxy
	int		sizeOfImage() const { return 0;}
private:
    Image* LoadImage() { // if not loaded yet: load
		    if (m_image == 0) {
				m_image = LoadImageFile(m_imageFile);
			}
			return m_image;
		}

private:
    Image*		m_image;		// ptr to actual file
    const char* m_imageFile;	// file name
};
 
// ===================================================================== //

int main () {
	
	// using only proxy, not actual file
	
	ProxyImage pimage = ProxyImage("ImageFile");
	int size = pimage.sizeOfImage();

	pimage->Draw(Point(50, 100));   // Draw() is a function of actual image, not proxy.
									// operator -> loads the image & enables calls to its functions
									
	(*pimage).Draw(Point(50, 100)); // same here 

}

