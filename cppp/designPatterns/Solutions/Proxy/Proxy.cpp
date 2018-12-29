#include <iostream>
using namespace std;

class Point {
public:
	Point(int x,int y) : x(x),y(y) {}
private:
	int x,y;
};

class Image {
  public:
	  virtual void Draw(const Point& p) { cout << "Point Draw" << endl;}
};

extern Image* LoadImageFile(const char*) { return new Image;}  
 
class ProxyImage {
public:
    ProxyImage(const char* imageFile) {
		    m_imageFile = imageFile;
			m_image = 0;
		}
    virtual ~ProxyImage() {}

    virtual Image* operator->() { return LoadImage();}
    virtual Image& operator*()  { return *LoadImage();}

	void	checkPassword() {}
	int		sizeOfImage() const { return 0;}
private:
    Image* LoadImage() {
		    if (m_image == 0) {
				m_image = LoadImageFile(m_imageFile);
			}
			return m_image;
		}

private:
    Image*		m_image;
    const char* m_imageFile;
};
 
//-----------------------------------------------------

int main () {

	ProxyImage pimage = ProxyImage("ImageFile");
	int size = pimage.sizeOfImage();

	pimage->Draw(Point(50, 100));  
	(*pimage).Draw(Point(50, 100));  

}

