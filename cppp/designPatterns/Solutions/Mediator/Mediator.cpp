#include <iostream>

using namespace std;

class NetComponent;
class NetPath;
class NetQoS;

//-------------------------------------------------------

class Mediator {
public:
	explicit Mediator(void) {}
	virtual ~Mediator(void) {}

	virtual void NetChanged(NetComponent*) = 0;

protected:
	Mediator(int);
	virtual void CreateNetComponents() = 0;
};

//-------------------------------------------------------

class LspMediator : public Mediator {
public:
	explicit LspMediator(int id) { lspId=id;}
	virtual ~LspMediator(void) {}

	virtual void NetChanged(NetComponent*);
	virtual void CreateNetComponents();
	void ChangePath(char*);
	void ChangeQoS(char*);

private:
	int lspId;
	NetPath* m_lspPath;
	NetQoS*	m_qosDescriptor;
};

//-------------------------------------------------------

class NetComponent {
public:
	explicit NetComponent(Mediator* md ) : m_mediator(md) {}
	virtual void Changed()  { m_mediator->NetChanged(this);}

protected:
	Mediator* m_mediator;
};

//-------------------------------------------------------

class NetPath : public NetComponent {
public:
	explicit NetPath(Mediator* md) : NetComponent(md) {}
	virtual ~NetPath(void) {}

	void CreateInitialPath(char* initPath);
	void GetNewPath(void) 
		{ cout << "NetPath path -> " << m_path << endl;}

	void ChangePath(char* newPath);
private:
	char* m_path;
};

void NetPath::CreateInitialPath(char* newPath) {
	m_path = newPath;
	cout << "Initial path -> " << m_path << endl;
}

void NetPath::ChangePath(char* newPath) {
	m_path = newPath;
	cout << "New NetPath path -> " << m_path << endl;
	Changed();
}

//-------------------------------------------------------

class NetQoS : public NetComponent {
public:
	explicit NetQoS(Mediator* md) : NetComponent(md) {}
	virtual ~NetQoS(void) {}

	void CreateInitialQoS(char* qos) {}
	void GetNewQoS(void) {}
	void ChangeQoS(char* qos) {}
private:
	char* m_QoS;
};

//-------------------------------------------------------

void LspMediator::NetChanged(NetComponent* w) {
	if (w == m_lspPath)
		// Change the path used by the LSP
		cout << "Mediator informed about change to LSP Path" << endl;
	else if (w == m_qosDescriptor)
		// Change the Qos resources used by the LSP
		cout << "Mediator informed about change to QoS Resources" << endl;
}

void LspMediator::CreateNetComponents() {
	m_lspPath = new NetPath(this);
	m_lspPath->CreateInitialPath("R2R3R4R5");

	m_qosDescriptor = new NetQoS(this);
	m_qosDescriptor->CreateInitialQoS("Initial QoS");
}

void LspMediator::ChangePath(char* newPath) {
	m_lspPath->ChangePath(newPath);
}

void LspMediator::ChangeQoS(char* newQoS) {
	m_qosDescriptor->ChangeQoS(newQoS);
}

//-------------------------------------------------------

int main() {
	LspMediator* Mediator = new LspMediator(555);
	Mediator->CreateNetComponents();
	Mediator->ChangePath("R2R6R5");
	Mediator->ChangeQoS("Changed Details");

	delete Mediator;

	return 0;
}

