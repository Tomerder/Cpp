#include <iostream>
using namespace std;

class Stack
{
public:
    friend class StackIter;

			Stack()			{ sp =  - 1; }
    void	push(int in)	{ items[++sp] = in; }
    int		pop()			{ return items[sp--]; }
    bool	isEmpty()		{ return (sp ==  - 1); }

    StackIter* createIterator()const;
private:
	int		items[10];
    int		sp;

};

class StackIter
{
  public:
    StackIter(const Stack* s)	{ m_stack = s; }

    void first()				{ m_index = 0; }
    void next()					{ m_index++; }
    bool isDone()				{ return m_index == m_stack->sp + 1; }
    int currentItem()			{ return m_stack->items[m_index];}
private:
    const Stack* m_stack;
    int			 m_index;

};

StackIter* Stack::createIterator()const
{
	return new StackIter(this);
}

bool operator == (const Stack &l, const Stack &r)
{
	// 3. Clients ask the container object to create an iterator object
	StackIter *itl = l.createIterator();
	StackIter *itr = r.createIterator();
	// 4. Clients use the first(), isDone(), next(), and currentItem() protocol
	for (itl->first(), itr->first(); !itl->isDone(); itl->next(), itr->next())
	{
		if (itl->currentItem() != itr->currentItem())
			break;
	}
	bool ans = itl->isDone() && itr->isDone();
	delete itl;
	delete itr;
	return ans;
}

int main()
{
	Stack s1;
	for (int i = 1; i < 5; i++) 
	{
		s1.push(i);
	}

	Stack s2(s1), s3(s1), s4(s1), s5(s1);
	s3.pop();
	s5.pop();
	s4.push(2);
	s5.push(9);

	cout << "1 == 2 is " << (s1 == s2) << endl;
	cout << "1 == 3 is " << (s1 == s3) << endl;
	cout << "1 == 4 is " << (s1 == s4) << endl;
	cout << "1 == 5 is " << (s1 == s5) << endl;

	return 0;
}
