/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-00-00    
    Last modified date:		2013-00-00
    Description: 	
****************************************************************************/


#include <vector>
#include <string>
#include <iostream>

#include "Story.h"
#include "Tokenizer.h"

using namespace std;



enum Choices
{
	EXIT,
	
	SEN_MK, 	SEN_ADD, 	SEN_RM, 	SEN_DEL,	SEN_PRT,
	CHAP_MK, 	CHAP_ADD, 	CHAP_RM, 	CHAP_DEL,	CHAP_PRT,
	SST_MK, 	SST_ADD, 	SST_RM, 	SST_DEL,	SST_PRT,
	NOV_MK, 	NOV_ADD, 	NOV_RM, 	NOV_DEL,	NOV_PRT,

	MENU = 100
};


// print choices
void PrintChoices(void)
{
	cout << "Create a sentence: " << SEN_MK << endl;
	cout << "Append a word to sentence: " << SEN_ADD << ", remove a word: " << SEN_RM << endl;
	cout << "Print stand-alone sentences: " << SEN_PRT << ", delete a sentence: " << SEN_DEL << endl;
	cout << endl;
	
	cout << "Create a chapter from sentences: " << CHAP_MK << endl;
	cout << "Append a sentence to chapter: " << CHAP_ADD << ", remove a sentence: " << CHAP_RM << endl;
	cout << "Print stand-alone chapters: " << CHAP_PRT  << ", delete a chapter: " << CHAP_DEL << endl;
	cout << endl;
	
	cout << "Create a story from sentences (will delete existing story, if there is one): " << SST_MK << endl;
	cout << "Append a sentence to story: " << SST_ADD << ", remove a sentence: " << SST_RM << endl;
	cout << "Print story: " << SST_PRT  << ", delete story: " << SST_DEL << endl;
	cout << endl;
	
	cout << "Create a novel from chapters (will delete existing novel, if there is one): " << NOV_MK << endl;
	cout << "Append a chapter to novel: " << NOV_ADD << ", remove a chapter: " << NOV_RM << endl;
	cout << "Print novel: " << NOV_PRT  << ", delete novel: " << NOV_DEL << endl;
	cout << endl;
	
	cout << "Print menu: " << MENU << endl;
	cout << "Exit: " << EXIT << endl;
}
// ===================================================================== //


template <class T>
void PrintTexts(vector<T*>& _vec)
{
	int end = _vec.size();
	
	for(int i=0; i<end; ++i)
	{
		cout << i+1 << ". ";
		_vec[i]->Print();
	}
	cout << endl;
}
// ===================================================================== //


int chooseWord(vector<Word_t*> _vec)
{
	size_t i;
	
	cout << "choose word by number: ";
	cin >> i;
	
	if(i<1 || i>_vec.size())
	{
		cout << "invalid number" << endl;
		return -1;
	}
	return (int)i-1;
}
// --------------------------------------------------------------------- //
int chooseSen(vector<Sentence_t*> _vec)
{
	size_t i;
	
	cout << "existing sentences:" << endl;
	PrintTexts<Sentence_t>(_vec);
	
	cout << "choose sentence by number: ";
	cin >> i;
	
	if(i<1 || i>_vec.size())
	{
		cout << "invalid number" << endl;
		return -1;
	}
	return (int)i-1;
}
// --------------------------------------------------------------------- //
int chooseChap(vector<Chapter_t*> _vec)
{
	size_t i;
	
	cout << "existing chapters:" << endl;
	PrintTexts<Chapter_t>(_vec);
	
	cout << "choose chapter by number: ";
	cin >> i;
	
	if(i<1 || i>_vec.size())
	{
		cout << "invalid number" << endl;
		return -1;
	}
	return (int)i-1;
}
// --------------------------------------------------------------------- //



// ===================================================================== //
//								MAIN
// ===================================================================== //
int main()
{
//	Tokenizer_t tok(" "); // tokenizer with delimiter = space
	
//	Word_t*		word = 0;
//	Sentence_t*	sen = 0;
//	Chapter_t*	ch = 0;
//	SStory_t*	story = 0;
//	Novel_t*	novel  = 0;
	
//	vector<Sentence_t*> sents;
//	vector<Chapter_t*>	chaps;
	
//	vector<Word_t*>* 	 words = 0;
//	vector<Sentence_t*>* sents2 = 0;
//	vector<Chapter_t*>*	 chaps2 = 0;
	
	string tempStr;
	int i, j;
	int choice;
	
	char temp;
	
	// starting by creating 1st sentence
	
	cout << "Enter a sentence (at least two words): ";
	cin >> tempStr;
	cin >> temp;
	
	
	sen = new Sentence_t();
	sents.push_back(sen);
	
	tok.Tokenize(tempStr);
	
	while(!tok.Empty())
	{
		word = new Word_t(tok.GetNextToken());
		sen->Add(word);
	}
	
	tempStr.clear();
	sen = 0;
	word = 0;
	
	
	
	
	cout << endl;
	PrintChoices();
	
	
	cout << "your choice1: " << choice << endl;
	cout << endl << "Enter your choice: " << endl;
	cin >> choice;
	cout << "your choice2: " << choice << endl;
	
	
	
	while(choice)
	{
		
		switch(choice)
		{
		
		case SEN_MK:
			cout << "SEN_MK" << endl;
			
			break;

		case SEN_ADD:
			cout << "SEN_ADD" << endl;
			
			break;
		
		case SEN_RM:
			cout << "SEN_RM" << endl;
			
			break;
		
		case MENU:
		
			PrintChoices();
			cout << endl;
			break;
			
		case EXIT:
		default:
		
			return 0;
			
		} // end switch
		
		cout << "Enter next choice (" << MENU << " for menu, " << EXIT << " to exit): ";
		cin >> choice;
	} // end choice
	
	return 0;
}


/*######################################################################*/


