#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Number;

class Memento
{
  public:
    Memento(int val)
    {
        m_state = val;
    }
  private:
    friend class Number; // not essential, but p287 suggests this
    int m_state;
};

class Number
{
  public:
    Number(int value)
    {
        m_value = value;
    }
    void dubl()
    {
        m_value = 2 * m_value;
    }
    void half()
    {
        m_value = m_value / 2;
    }
    int getValue()
    {
        return m_value;
    }
    Memento *createMemento()
    {
        return new Memento(m_value);
    }
    void reinstateMemento(Memento* mem)
    {
        m_value = mem->m_state;
    }
  private:
    int m_value;
};

class Command
{
  public:
    typedef void(Number:: *Action)();
    Command(Number* receiver, Action action)
    {
        m_receiver = receiver;
        m_action = action;
    }
    virtual void execute()
    {
        m_mementoList[m_numCommands] = m_receiver->createMemento();
        m_commandList[m_numCommands] = this;
        if (m_numCommands > m_highWater)
          m_highWater = m_numCommands;
        m_numCommands++;
        (m_receiver->*m_action)();
    }
    static void undo()
    {
        if (m_numCommands == 0)
        {
            cout << "*** Attempt to run off the end!! ***" << endl;
            return ;
        }
        m_commandList[m_numCommands - 1]->m_receiver->reinstateMemento
          (m_mementoList[m_numCommands - 1]);
        m_numCommands--;
    }
    void static redo()
    {
        if (m_numCommands > m_highWater)
        {
            cout << "*** Attempt to run off the end!! ***" << endl;
            return ;
        }
        (m_commandList[m_numCommands]->m_receiver->*(m_commandList[m_numCommands]->m_action))();
        m_numCommands++;
    }
  protected:
    Number*			m_receiver;
    Action			m_action;
    static Command* m_commandList[20];
    static Memento* m_mementoList[20];
    static int		m_numCommands;
    static int		m_highWater;
};

Command *Command::m_commandList[];
Memento *Command::m_mementoList[];
int Command::m_numCommands = 0;
int Command::m_highWater = 0;

int main()
{
  int i;
  cout << "Integer: ";
  cin >> i;
  Number* object = new Number(i);

  Command* commands[3];
  commands[1] = new Command(object, &Number::dubl);
  commands[2] = new Command(object, &Number::half);

  cout << "Exit[0], Double[1], Half[2], Undo[3], Redo[4]: ";
  cin >> i;

  while (i)
  {
    if (i == 3)
      Command::undo();
    else if (i == 4)
      Command::redo();
    else
      commands[i]->execute();
    cout << "   " << object->getValue() << endl;
    cout << "Exit[0], Double[1], Half[2], Undo[3], Redo[4]: ";
    cin >> i;
  }
}
