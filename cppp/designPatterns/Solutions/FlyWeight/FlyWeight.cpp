#include <set>
using namespace std;

typedef float Coord;

class Window;
class GlyphContext;
class Font {
  public:
	  Font(char*) {}
};

//=====================================================================
class Glyph {
public:
	virtual ~Glyph()								{}
	
	virtual void	Draw(Window*, GlyphContext&)	{}

	virtual void	SetFont(Font*, GlyphContext&)	{}
	virtual Font*	GetFont(GlyphContext&)			{ return 0;}

	virtual void	First(GlyphContext&)			{}
	virtual void	Next(GlyphContext&)				{}
	virtual bool	IsDone(GlyphContext&)			{ return true;}
	virtual Glyph*	Current(GlyphContext&)			{ return 0;}

	virtual void	Insert(Glyph*, GlyphContext&)	{}
	virtual void	Remove(GlyphContext&)			{}
protected:
	Glyph() {}
};
//=====================================================================

class Character : public Glyph {
public:
	Character(char) {}

	virtual void Draw(Window*, GlyphContext&)	{}
private:
    char m_charcode;
};
//=====================================================================

class GlyphContext {
public:
	GlyphContext()								{}
	virtual ~GlyphContext()						{}

	virtual void Next(int step = 1)				{}
	virtual void Insert(int quantity = 1)		{}

	virtual Font* GetFont()						{ return 0;}
	virtual void SetFont(Font*, int span = 1)	{}
private:
    int			m_index;
	std::set<Font*>	m_fonts;
};

//=====================================================================

class Row {};
class Column {};
//=====================================================================

const int NCHARCODES = 128;

class GlyphFactory {
public:
    GlyphFactory();
	virtual ~GlyphFactory() {}

    virtual Character* CreateCharacter(char);
    virtual Row* CreateRow();
    virtual Column* CreateColumn();
private:
    Character* m_character[NCHARCODES];
};

GlyphFactory::GlyphFactory () {
    for (int i = 0; i < NCHARCODES; ++i) {
         m_character[i] = 0;
    }
}

Character* GlyphFactory::CreateCharacter (char c) {
    if (!m_character[c]) {
        m_character[c] = new Character(c);
    }

    return m_character[c];
}

Row* GlyphFactory::CreateRow () {
    return new Row;
}

Column* GlyphFactory::CreateColumn () {
    return new Column;
}

int main() {
	GlyphContext gc;
	Font* times12           = new Font("Times-Roman-12");
	Font* timesItalic12		= new Font("Times-Italic-12");
	gc.SetFont(times12, 6);
	gc.Insert(6);
	gc.SetFont(timesItalic12, 6);
	return 0;
}
