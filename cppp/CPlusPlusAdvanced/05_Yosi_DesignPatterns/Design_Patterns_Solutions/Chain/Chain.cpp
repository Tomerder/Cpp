#include <iostream>
#include <string>
using namespace std;

enum ReqType { Help_e, Print_e, Preview_e};

enum Topic { noHelp_e, isHelp_e, applic_e, show_e, press_e };

// --------------------------------------------------------------------- //
class Request {
public:
	Request(const char* req, ReqType t) : kind(t) 
			{ cout << req << endl;}
	const char*	RequestName() const 
			{ return reqName.c_str();}
	int GetKind() 
			{ return kind;}
private:
	ReqType kind;
	string reqName;
};
// --------------------------------------------------------------------- //


// --------------------------------------------------------------------- //
//							Request Types
// --------------------------------------------------------------------- //
class HelpRequest	: public Request 	{ 
	HelpRequest() : Request("HelpRequest",Help_e)	{}
};
// --------------------------------------------------------------------- //
class PrintRequest	: public Request {	
	PrintRequest() : Request("PrintRequest",Print_e) {}
};
// --------------------------------------------------------------------- //
class PreviewRequest	: public Request 	{ 
	PreviewRequest() : Request("PreviewRequest",Preview_e)	{}
};
// --------------------------------------------------------------------- //

class Handler {
public:
	virtual void	HandleRequest(Request* r) {
		switch (r->GetKind()) {	// what is the request?
			case Preview_e:
				HandlePreview((PreviewRequest*) r);	break;
			case Print_e:
				HandlePrint((PrintRequest*) r);		break;
			case Help_e: 
				HandleHelp((HelpRequest*) r);		break;
			default:	break;
		}
	}
			
	void	HandlePrint(PrintRequest* r)	
		{ cout << "Handler::HandlePrint()" << endl;}
	void	HandlePreview(PreviewRequest* r)
		{ cout << "Handler::HandlePreview()" << endl;}
	void	HandleHelp(HelpRequest* r)
		{ cout << "Handler::HandleHelp()" << endl;}
};
// --------------------------------------------------------------------- //

// handle request of type Help_e
class HelpHandler {
public:
    HelpHandler(HelpHandler* h = 0, Topic t = noHelp_e)
		    : m_successor(h), m_topic(t) { }

	virtual bool HasHelp() { return m_topic != noHelp_e;}
    virtual void SetHandler(HelpHandler* h, Topic t) // set successor
		{ m_successor = h; m_topic = t;}
    virtual void HandleHelp() {	// call successor if exists
		cout << "HelpHandler::HandleHelp()" << endl;
		if (m_successor != 0) {
			m_successor->HandleHelp();
		} else {
		}
	}
    virtual void HandleRequest(Request* req) {
		cout << req->RequestName() << endl;
		switch (req->GetKind()) {
			case Help_e: cout << "HelpHandle Request" << endl; break;
			default: ;  // other requests
		}
	}
private:
    HelpHandler*	m_successor;	// next in chain
    Topic			m_topic;
};
// --------------------------------------------------------------------- //

class Widget : public HelpHandler {
protected:
    Widget(Widget* w, Topic t = noHelp_e) : HelpHandler(w,t),m_parent(w){}
private:
    Widget* m_parent;
};
// --------------------------------------------------------------------- //


class Button : public Widget {
public:
    Button(Widget* w, Topic t = noHelp_e) : Widget(w, t) { }

    virtual void HandleHelp() {
		if (HasHelp())  cout << "Button Help" << endl;
		else			HelpHandler::HandleHelp();
	}
};
// --------------------------------------------------------------------- //

class Dialog : public Widget {
public:
    Dialog(HelpHandler* h, Topic t = noHelp_e) : Widget(0) 
		{ SetHandler(h, t);}	// HelpHandler::SetHandler
    virtual void HandleHelp() {
		if (HasHelp())	cout << "Dialog Help" << endl;
		else			HelpHandler::HandleHelp();
	}
};
// --------------------------------------------------------------------- //


class Application : public HelpHandler {
public:
    Application(Topic t) : HelpHandler(0, t) { }

    virtual void HandleHelp() { cout << "Application::HandleHelp" << endl;} // application specifics
};

// ===================================================================== //


int main () {

	Application* app = new Application(applic_e);
	Dialog*		 dlg = new Dialog(app, show_e);
//	Button*		 btn = new Button(dlg, press_e);
	Button*		 btn = new Button(dlg, noHelp_e);
	
	btn->HandleHelp();
	
	return 0;
}


