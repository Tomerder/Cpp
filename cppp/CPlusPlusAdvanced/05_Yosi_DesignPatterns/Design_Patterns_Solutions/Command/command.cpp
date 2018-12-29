#include <list>
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

// example: document & applications
// document can be opened in different applications,
// and all have the same commands: open, copy, paste etc.,
// but executed in different ways

class Document {
  public:
			Document(const string& docName)		{ m_docName = docName;}
	  void	Open()								{ cout << "Open"  << endl;}
	  void	Paste()								{ cout << "Paste" << endl;}
	  const char* DocName() const				{ return m_docName.c_str();}
private:
	string	m_docName;
};

class Application {
  public:
			Application()		{}
	  void	Add(Document* doc)	{ cout << "Document " << doc->DocName() << " added " << endl;}
};

class Command {
public:
    virtual		~Command() {}

    virtual void Execute() = 0;
protected:
    Command() {}
};

class OpenCommand : public Command {
public:
    OpenCommand(Application* app, const string& docName) 
	{ 
		m_application = app;
		m_docName = docName;
	}

    virtual void Execut e() {
				Document* document = new Document(m_docName);
				m_application->Add(document);
				document->Open();			
		}

private:
    Application*	m_application;
    char*			m_response;
	string			m_docName;
};


class PasteCommand : public Command {
public:
    PasteCommand(Document* doc)	{ m_document = doc;}
    virtual void Execute() { 
		m_document->Paste();
	}
private: 
    Document*		m_document;
};

// macro - list of commands to execute in order, with a single call
class MacroCommand : public Command {
public:
			MacroCommand() {}
	virtual ~MacroCommand() {}

    virtual void Add(Command* c) { m_cmds.push_back(c);}
    virtual void Remove(Command* c ) {
		    list<Command*>::iterator i = find(m_cmds.begin(),m_cmds.end(),c);
			if (i != m_cmds.end()) m_cmds.erase(i);
		}

    virtual void Execute() {
		    list<Command*>::iterator i;
			for (i = m_cmds.begin(); i != m_cmds.end(); ++i) {
				Command* c = *i;
				c->Execute();
			}
		}
private:
    list<Command*> m_cmds;
};

int main() {

	Application		app;

	Document		doc1("Yosi.doc"); 
	Command* openCmd1 = new OpenCommand(&app,doc1.DocName());
	Command* pastCmd1 = new PasteCommand(&doc1);

	openCmd1->Execute();
	pastCmd1->Execute();

	Document		doc2("Rita.jpg"); 
	Command* openCmd2 = new OpenCommand(&app,doc2.DocName());
	Command* pastCmd2 = new PasteCommand(&doc2);

	MacroCommand	mc;
	mc.Add(openCmd2);
	mc.Add(pastCmd2);
	mc.Execute();

	return 0;
}

