#include <iostream>
using namespace std;


class VisualComponent {
public:
    VisualComponent() {}

    virtual void Draw() = 0;
    virtual void Resize() {}
};
// --------------------------------------------------------------------- //

class Decorator : public VisualComponent {	// the decorator is a visual component
public:
    Decorator(VisualComponent* vc) { m_component = vc;}
    virtual void Draw()		{ 
		if (m_component)  m_component->Draw();
	}
    virtual void Resize()	{ m_component->Resize();}
private:
    VisualComponent* m_component;
};
// --------------------------------------------------------------------- //

class BorderDecorator : public Decorator {
public:
    BorderDecorator(VisualComponent* vc, int borderWidth ) 
		: Decorator(vc), m_width(borderWidth) {}

    virtual void Draw() {
		Decorator::Draw();
		DrawBorder(m_width);
	}
private:
    void DrawBorder(int) { cout << "BorderDecorator" << endl;}
private:
	VisualComponent* m_vc;
    int m_width;
};
// --------------------------------------------------------------------- //
class ScrollDecorator : public Decorator {
public:
    ScrollDecorator(VisualComponent* vc) 
		: Decorator(vc) {}
   virtual void Draw() {
		Decorator::Draw();
		Scroll();
	}
private:
    void Scroll() { cout << "ScrollDecorator" << endl;}
private:
	VisualComponent* m_vc;
};
// --------------------------------------------------------------------- //
class TextView : public VisualComponent {
public:
	    virtual void Draw() { cout << "TextView" << endl;}
};

// ===================================================================== //

int main () {

	TextView	textView;
	
	ScrollDecorator sd(&textView);
	ScrollDecorator sd1 = sd;
	BorderDecorator bd(&sd,1);
//	bd.Draw();
//	sd.Draw();
	
	BorderDecorator bd2(&textView,1);
	ScrollDecorator sd2(&bd2);
//	bd2.Draw();
//	sd2.Draw();
	
	textView.Draw();
	
	return 0;
}

/*

TextView
ScrollDecorator
BorderDecorator

*/

