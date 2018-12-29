/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-07    
    Last modified date:		2013-11-08
    Description: 	test for Story - template version
****************************************************************************/


#include <iostream>
#include "Story.h"
using namespace std;


int main()
{
	Word_t* hello = new Word_t("Hello");
	Word_t* world = new Word_t("World");
	
	hello->Print();
	world->Print();
	cout << endl;
	
	Sentence_t* one = new Sentence_t;
	
	one->Print();

	try {
		one->Add(hello);
	}
	catch(const char* excep)
	{
		cout << excep << endl;
	}
	
	one->Print();
	
	try {
		one->Add(world);
	}
	catch(const char* excep)
	{
		cout << excep << endl;
	}
	
	one->Print();
	
	try {
		one->Remove(hello);
	}
	catch(const char* excep)
	{
		cout << excep << endl;
	}
	
	one->Print();
	
	
	Word_t* good = new Word_t("Good");
	Word_t* morning = new Word_t("Morning");
	
	
	Sentence_t* two = new Sentence_t;
	
	two->Print();

	try {
		two->Add(good);
		two->Add(morning);
	}
	catch(const char* excep)
	{
		cout << excep << endl;
	}
	
	two->Print();
	
	
	Sentence_t* three = new Sentence_t;
	
	string sen3[] = { "It", "was", "a", "dark", "and", "stormy", "night" };	
	Word_t* sen3ptr[7];
	
	for(int i=0; i<7; ++i)
	{
		sen3ptr[i] = new Word_t(sen3[i]);
		three->Add(sen3ptr[i]);
	}
	
	three->Print();
	
	
	Chapter_t* ch1 = new Chapter_t("Chapter 1");
	
	try {
		ch1->Add(two);
		ch1->Add(one);
	}
	catch(const char* excep)
	{
		cout << excep << endl;
	}
	
	ch1->Print();
	
	Chapter_t* ch2 = new Chapter_t("Chapter 2");
	
	try {
		ch2->Add(three);
	}
	catch(const char* excep)
	{
		cout << excep << endl;
	}
	
	ch2->Print();
	
	
	// STORY //
	
#ifndef NO_STORY

	Story_t<Chapter_t>* myStory = new Story_t<Chapter_t>("A Story");
	try {
		myStory->Add(ch1);
		myStory->Add(ch2);
	}
	catch(const char* excep)
	{
		cout << excep << endl;
	}
	
	myStory->Print();
	
	delete myStory;

#else

	delete ch1;
	delete ch2;

#endif /* NO_STORY */

	
	
	return 0;
}

/*######################################################################*/

