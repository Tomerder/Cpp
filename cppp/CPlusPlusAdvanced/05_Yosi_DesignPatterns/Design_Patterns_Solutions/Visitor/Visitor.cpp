#include <iostream>
#include <list>
#include <algorithm>
#include <string>

using namespace std;

class RegularFile;
class SpecialFile;
class Directory;

class Visitor {  // abstract
public:
    virtual void visit (RegularFile*)	= 0;
    virtual void visit (SpecialFile*)	= 0;
    virtual void visit (Directory*)		= 0;
};


class File {  // abstract element
public:
	File(const char* fn) : m_name(fn) {}
    virtual void accept (Visitor& v) = 0; 
    string name () const { return m_name;}
protected:
    File (const string&);
private:
    string m_name;
};

class Directory : public File {
public:
	Directory(const char* fn) : File(fn) {}
    virtual void accept (Visitor& v);
    virtual void add (File*) throw (domain_error);
    virtual void remove (File* fp) throw (domain_error) {}
    typedef list<File*>::iterator FileIterator;
private:
    list <File*> m_children;
};


class RegularFile : public File {
public:
	RegularFile(const char* fn) : File(fn) {}
    virtual void accept (Visitor& v) { v.visit(this);}
			void print() const { cout << "print " << endl;}	
			void insert(const string& s) { m_contents = s;}	
private:
    string m_contents;
};


class SpecialFile : public File {
public:
	SpecialFile(const char* fn) : File(fn) {}
    virtual void accept (Visitor& v) { v.visit (this); }
			void length() const { cout << "file length " << endl;}	
};


class SameFile { // predicate
public:
    SameFile (File*& f) : m_f(f) {}             
    bool operator () (File*& f) {
       return f->name () == m_f->name ();
    }
private:
    File* m_f;
};

void Directory::add (File* f) throw (domain_error) {
	if (find_if (m_children.begin (), m_children.end (), 
		SameFile (f)) != m_children.end ())
		throw invalid_argument ("duplicate name"); // ? 
    m_children.insert (m_children.end (), f);
}


void Directory::accept (Visitor& v) { 
	// first, visit every child
    for (FileIterator	i =  m_children.begin (); 
						i != m_children.end (); ++i) {
      File* f = *i;
      f->accept (v);
    }  // finally, visit this composite object
    v.visit (this); // or: bind iteration strategy here             
}
  

// The Visitor class accumulates information processed while visiting the hierarchy. 

class CountingVisitor : public Visitor { // implements
// counts the number of regular and special files
public:
    CountingVisitor () : m_reg(0), m_spec(0) {}

    virtual void visit (RegularFile* af)	{  ++m_reg;}
    virtual void visit (SpecialFile* bf)	{  ++m_spec;}
    virtual void visit (Directory* dir)	{}
    int getSpecial () const {  return m_spec;}
    int getRegular () const {  return m_reg;}
private:
    int m_reg;
    int m_spec;
};
  
class ShowingVisitor : public Visitor { // implements
// shows the contents of all visited files
public:
    virtual void visit (RegularFile* af )	{ af->print(); }  
    virtual void visit (SpecialFile* bf)	{ bf->length();}
    virtual void visit (Directory* dir)	{ }
};


int main() {
	Directory*		root= new Directory("root");
	RegularFile*	f	= new RegularFile("asci_1");
	
	f->insert (string("file name is asci_1")); 
	root->add(f);
	f = new RegularFile("asci_2");
	f->insert (string("file name is asci_2")); 
	root->add(f);
	
	root->add (new SpecialFile ("binary_1"));
	root->add (new SpecialFile ("binary_2"));
	
	Directory* dir = new Directory("Directory"); 
	root->add(dir);
	dir->add(f);
	
	CountingVisitor cv; 
	root->accept(cv);
	
	ShowingVisitor sw; 
	root->accept(sw);

	cout	<< "There are " << cv.getRegular () 
			<< " regular files" << endl;
	cout	<< "There are " << cv.getSpecial () 
			<< " special files" << endl;

	return 0;
}
