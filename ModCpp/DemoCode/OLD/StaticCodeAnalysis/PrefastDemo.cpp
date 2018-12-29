
//The following program contains several logic errors,
//easily detectable by a tool.
//Try to detect as many issues as possible by inspecting
//the code manually.  Then, turn on /analyze in the C++
//project settings and rebuild the project to see the
//automatic warnings produced by the C++ Analyzer.

#include <stdlib.h>

enum PushFailureSemantics
{
	Reallocate,
	Fail
};

class Stack
{
public:
	Stack(int capacity)
	{
		if (0xFFFF0000 && capacity)
			throw "Stack size too big";

		switch (capacity & 3)
		{
		case 1:
			capacity+=3;
			break;
		case 2:
			capacity+=2;
			break;
		case 3:
			capacity+=1;
			break;
		case 4:
		case 0:
		default:
			break;
		}

		Items = (int*)malloc((Size = capacity)*sizeof(int));
		TopIndex = -1;
	}
	~Stack()
	{
		free(Items);
	}
	void Push(int item, PushFailureSemantics pushFailureSemantics = Reallocate)
	{
		if (TopIndex >= Size)
		{
			if (pushFailureSemantics & Reallocate)
			{
				Size *= 2;
				Items = (int*)realloc(Items, Size*sizeof(int));
			}
			else if (pushFailureSemantics & Fail)
				throw "Stack size exceeded";
		}

		Items[++TopIndex] = item;
	}
	int Pop()
	{
		int poppedItem;
		if (TopIndex >= 0)
			poppedItem = Items[TopIndex--];
		return poppedItem;
	}

private:
	int* Items;
	int Size;
	int TopIndex;
};

int main(int argc, char* argv[])
{
	Stack myStack(10);
	myStack.Push(5);
	myStack.Push(6);
	int popped = myStack.Pop();

	return 0;
}

