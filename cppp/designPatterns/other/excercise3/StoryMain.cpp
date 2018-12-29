/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-07    
    Last modified date:		2013-11-09
    Description: 	test for Story.
****************************************************************************/

#ifndef _INTERACTIVE


#include <iostream>
#include "Story.h"
using namespace std;


int main()
{
	Word_t* hello = new Word_t("Hello");
	Word_t* world = new Word_t("World");
	
	cout << endl << "*** stand-alone words:" << endl;
	hello->Print();
	cout << endl;
	world->Print();
	cout << endl;
	
	Sentence_t* one = new Sentence_t;
	
	cout << endl << "*** empty sentence:" << endl;
	one->Print();

	try {
		one->Add(hello);
		one->Add(world);
	}
	catch(const char* excep)
	{
		cout << excep << endl;
	}
	
	cout << endl << "*** sentence with words:" << endl;
	one->Print();
	
	try {
		one->Remove(hello);
	}
	catch(const char* excep)
	{
		cout << excep << endl;
	}
	
	cout << endl << "*** deleted a word:" << endl;
	one->Print();
	
	
	Word_t* good = new Word_t("Good");
	Word_t* morning = new Word_t("Morning");
	
	
	Sentence_t* two = new Sentence_t;

	try {
		two->Add(good);
		two->Add(morning);
	}
	catch(const char* excep)
	{
		cout << excep << endl;
	}
	
	cout << endl << "*** sentence #2:" << endl;
	two->Print();
	
	
	Sentence_t* three = new Sentence_t;
	
	string sen3[] = { "It", "was", "a", "dark", "and", "stormy", "night" };	
	Word_t* sen3ptr[7];
	
	for(int i=0; i<7; ++i)
	{
		sen3ptr[i] = new Word_t(sen3[i]);
		three->Add(sen3ptr[i]);
	}
	
	cout << endl << "*** sentence #3:" << endl;
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
	
	cout << endl << "*** chapter from sentences 1&2:" << endl;
	ch1->Print();
	
	Chapter_t* ch2 = new Chapter_t("Chapter 2");
	
	try {
		ch2->Add(three);
	}
	catch(const char* excep)
	{
		cout << excep << endl;
	}
	
	cout << "*** chapter from sentence 3:" << endl;
	ch2->Print();
	
	cout << endl << "*** attempt to remove non-existing sentence:" << endl;
	try {
		ch2->Remove(one);
	}
	catch(const char* excep)
	{
		cout << excep << endl;
	}
	
	
	// Novel //
	
	Novel_t* nov = new Novel_t("A Novel");
	try {
		nov->Add(ch1);
		nov->Add(ch2);
	}
	catch(const char* excep)
	{
		cout << excep << endl;
	}
	
	cout << endl << "*** novel from chapters:" << endl;
	nov->Print();
	
	
	Sentence_t* four = new Sentence_t(*three);
	cout << endl << "*** new sentence copy-constucted from #3:" << endl;
	four->Print();
	
	Sentence_t* five = new Sentence_t;
	*five = *two;
	cout << endl << "*** new sentence assigned from #2:" << endl;
	five->Print();
	
	// Story //
	
	SStory_t* story = new SStory_t("A Story");
	try {
		story->Add(four);
		story->Add(five);
	}
	catch(const char* excep)
	{
		cout << excep << endl;
	}
	
	cout << endl << "*** story from these sentences:" << endl;
	story->Print();
	
	delete nov;
	delete story;
	
	return 0;
}

#endif /* #ifndef _INTERACTIVE */

/*######################################################################*/

