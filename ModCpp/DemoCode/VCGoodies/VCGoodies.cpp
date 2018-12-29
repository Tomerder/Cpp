// VCGoodies.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>
#include <string>
#include <iostream>
#include <thread>


// GS 
__declspec(noinline) void buffer_overrun()
{
	char buffer[10];
	//gets(buffer);
	printf("you said: %s\n", buffer);

}

int WINAPI Foo(int a, int b) // WINAPI == __stdcall == paremeters pass on stack, and the func take them from the stack in return
{
	return a + b;
}


void createLeakString()
{
	static int index = 0;

	for (int i = 0; i < 100; i++)
	{
		std::string *strPtr = new std::string("Leaking string " + std::to_string(index) + ":" + std::to_string(i));
	}
}

int main()
{
	//buffer_overrun();

	// in default, in C, paremeters pass on stack, and I am taking them from stack and not the function.
	// funcation stdcall will take them, and then the my code will try to take them too
	int(*pfn)(int, int) = (int(*)(int, int)) Foo; 
	//pfn(3, 3);


	for (int i = 0; i < 10000; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		createLeakString();
	}

	return 0;
}

