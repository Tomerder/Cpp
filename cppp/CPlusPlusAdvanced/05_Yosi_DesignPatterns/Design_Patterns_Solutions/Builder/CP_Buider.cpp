#include <iostream>
#include <list>
#include <algorithm>
#include <string>

using namespace std;

enum IOType { File, Folder };

struct IO {
	IOType  type;
	char    value[128];
};

class IOpackage {
public:
	IOpackage( char* type )  		{ what = type;}
	void setFile( const char* f)  	{ name = f;}	
	void setFolder( const char* f)  { name = f;}	
	char* getState() const			{ return (char*)what.c_str(); }
private:
	string what;
	string name;
};




class Builder {
public:
	virtual void configureFile( char* )    = 0;
	virtual void configureFolder( char* )  = 0;
	char* getState() const { return m_pack->getState(); }
protected:
	IOpackage*  m_pack;
};


class UnixBuilder : public Builder {
public:
	UnixBuilder() { m_pack = 
			new IOpackage( "Unix" ); }
	void configureFile( char* f )  
		{ m_pack->setFile( f ); }
	void configureFolder( char* f ) 
		{ m_pack->setFolder( f ); }
};


class PcBuilder : public Builder {
public:
	PcBuilder() { m_pack = 
		new IOpackage( "PC" ); }
	void configureFile( char* f )    
		{ m_pack->setFile( f ); }
	void configureFolder( char* f )  
		{ m_pack->setFolder( f ); }
};

class Reader {
public:
	void setBuilder( Builder* b ) { m_builder = b; }
	void construct( IO* list , int  num) {
		for (int i=0; i < num; i++)
			if (list[i].type == File)
				m_builder->configureFile((char*) list[i].value);
			else if (list[i].type == Folder)
				m_builder->configureFolder((char*) list[i].value);
	}
private:	
	Builder* m_builder;
};




int main() {

	UnixBuilder  	unixBuilder;
	PcBuilder    	pcBuilder;
	Reader       	reader;

	const int  Entries = 4;
	IO ioInp[Entries] = {  	{ File,  "Yosi.txt"},  
				     		{ File,  "Rita.txt"}, 
			                { Folder,"Ilan"}, 	       
							{ Folder,"Gilad"} 
						};

	reader.setBuilder( &unixBuilder );
	reader.construct( (IO*)ioInp, Entries );
	cout << unixBuilder.getState() << endl;

	reader.setBuilder( &pcBuilder );
	reader.construct( (IO*)ioInp, Entries );
	cout << pcBuilder.getState() << endl;

	return 0;
}

