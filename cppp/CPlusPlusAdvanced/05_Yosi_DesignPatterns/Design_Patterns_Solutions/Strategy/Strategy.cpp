#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

class Strategy
{
public:
    Strategy(int width): m_width(width){}
    void format()
    {
        char line[80], word[30];
        ifstream inFile("text.txt", ios::in);
        line[0] = '\0';

        inFile >> word;
        strcat(line, word);
        while (inFile >> word)
        {
            if (strlen(line) + strlen(word) + 1 > m_width)
				justify(line);
            else
				strcat(line, " ");
            strcat(line, word);
        }
        justify(line);
    }
protected:
    int m_width;
private:
    virtual void justify(char* line) = 0;
};

class LeftStrategy: public Strategy
{
public:
    LeftStrategy(int width): Strategy(width){}
private:
    virtual void justify(char* line)
    {
        cout << line << endl;
        line[0] = '\0';
    }
};

class RightStrategy: public Strategy
{
public:
    RightStrategy(int width): Strategy(width){}
private:
    virtual void justify(char *line)
    {
        char buf[80];
        int offset = m_width - strlen(line);
        memset(buf, ' ', 80);
        strcpy(&(buf[offset]), line);
        cout << buf << endl;
        line[0] = '\0';
    }
};

class CenterStrategy: public Strategy
{
public:
    CenterStrategy(int width): Strategy(width){}
private:
    virtual void justify(char *line)
    {
        char buf[80];
        int offset = (m_width - strlen(line)) / 2;
        memset(buf, ' ', 80);
        strcpy(&(buf[offset]), line);
        cout << buf << endl;
        line[0] = '\0';
    }
};

class TestStrategy {
public:
    enum StrategyType	{ Dummy, Left, Right, Center };

    TestStrategy()		{ m_strategy = 0; }
    void setStrategy(int type, int width);
    void doIt();
private:
    Strategy*	m_strategy;
};

void TestStrategy::setStrategy(int type, int width)
{
	delete m_strategy;
	if (type == Left)
		m_strategy = new LeftStrategy(width);
	else if (type == Right)
		m_strategy = new RightStrategy(width);
	else if (type == Center)
		m_strategy = new CenterStrategy(width);
}

void TestStrategy::doIt()
{
	m_strategy->format();
}

int main()
{
	TestStrategy test;
	int answer, width;
	cout << "Exit(0) Left(1) Right(2) Center(3): ";
	cin >> answer;
	while (answer)
	{
		cout << "Width: ";
		cin >> width;
		test.setStrategy(answer, width);
		test.doIt();
		cout << "Enter Exit(0) Left(1) Right(2) Center(3) : ";
		cin >> answer;
	}
	return 0;
}
