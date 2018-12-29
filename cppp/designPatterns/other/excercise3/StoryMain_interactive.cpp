/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-07    
    Last modified date:		2013-11-09
    Description: 	interactive test for Story - currently not working
****************************************************************************/


#ifdef _INTERACTIVE


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
	Tokenizer_t tok(" "); // tokenizer with delimiter = space
	
	Word_t*		word = 0;
	Sentence_t*	sen = 0;
	Chapter_t*	ch = 0;
	SStory_t*	story = 0;
	Novel_t*	novel  = 0;
	
	vector<Sentence_t*> sents;
	vector<Chapter_t*>	chaps;
	
	vector<Word_t*>* 	 words = 0;
	vector<Sentence_t*>* sents2 = 0;
	vector<Chapter_t*>*	 chaps2 = 0;
	
	string tempStr;
	char temp;
	int i, j;
	int choice = SEN_MK;
	
	
	// starting by creating 1st sentence
	
	cout << "Enter a sentence (at least two words): ";
	cin >> tempStr;
	
	
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
	cin >> temp;
	cin >> choice;
	cout << "your choice2: " << choice << endl;
	
	while(choice)
	{
		
		switch(choice)
		{
				
// --------------------------------------------------------------------- //
//							Sentences
// --------------------------------------------------------------------- //
		
		case SEN_MK:					// create sentence
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
			break;
		
		case SEN_ADD:			// add word to sentence
			
			i = chooseSen(sents);
			if(-1==i)
				break;
			
			cout << "Enter a word: ";
			cin >> tempStr;
			word = new Word_t(tempStr);
			
			sents[i]->Add(word);
			
			tempStr.clear();
			word = 0;
			
			cout << "new sentence: ";
			sents[i]->Print();
			break;
		
		case SEN_RM:			// remove word from sentence
			i = chooseSen(sents);
			if(-1==i)
				break;
			
			words = (vector<Word_t*>*)(sents[i]->GetChildren());
			
			j = chooseWord(*words);
			if(-1==j)
				break;
			
			sents[i]->Remove((*words)[j]);
			words->clear();
			
			cout << "new sentence: ";
			sents[i]->Print();
			break;
			
		case SEN_DEL:			// delete sentence
			i = chooseSen(sents);
			if(-1==i)
				break;
			
			delete sents[i];
			sents.erase(sents.begin()+i);
			break;
		
		case SEN_PRT:
			PrintTexts<Sentence_t>(sents);
			break;
		
		
		
// --------------------------------------------------------------------- //
//							Chapters
// --------------------------------------------------------------------- //
		
		case CHAP_MK:				// create a chapter
			cout << "Enter chapter title: ";
			cin >> tempStr;
			
			ch = new Chapter_t(tempStr);
			chaps.push_back(ch);
			
			ch = 0;
			tempStr.clear();
			break;
		
		case CHAP_ADD:			// add sentence to chapter
			i = chooseChap(chaps);
			if(-1==i)
				break;
			
			j = chooseSen(sents);
			if(-1==j)
				break;
			
			chaps[i]->Add(sents[j]);
			sents.erase(sents.begin()+j);
			
			cout << "chapter is now: ";
			chaps[i]->Print();
			break;
		
		case CHAP_RM:			// remove sentence from chapter
			i = chooseChap(chaps);
			if(-1==i)
				break;
			
			sents2 = (vector<Sentence_t*>*)(chaps[i]->GetChildren());
			
			j = chooseSen(*sents2);
			if(-1==j)
				break;
			
			chaps[i]->Remove((*sents2)[j]);
			sents2->clear();
			
			cout << "chapter is now: ";
			chaps[i]->Print();
			break;
			
		case CHAP_DEL:			// delete chapter
			i = chooseChap(chaps);
			if(-1==i)
				break;
			
			delete chaps[i];
			
			chaps.erase(chaps.begin()+i);
			break;
		
		case CHAP_PRT:
			PrintTexts<Chapter_t>(chaps);
			break;
		
		
		
// --------------------------------------------------------------------- //
//							Story
// --------------------------------------------------------------------- //
		
		case SST_MK:				// create a story
			cout << "Enter story title: ";
			cin >> tempStr;
			
			if(story) { delete story; }
			story = new SStory_t(tempStr);
			
			tempStr.clear();
			break;
		
		case SST_ADD:			// add sentence to story
			j = chooseSen(sents);
			if(-1==j)
				break;
			
			story->Add(sents[j]);
			sents.erase(sents.begin()+j);
			
			cout << "story is now: ";
			story->Print();
			break;
		
		case SST_RM:			// remove sentence from story
			sents2 = (vector<Sentence_t*>*)(story->GetChildren());
			
			j = chooseSen(*sents2);
			if(-1==j)
				break;
			
			story->Remove((*sents2)[j]);
			sents2->clear();
			
			cout << "story is now: ";
			story->Print();
			break;
			
		case SST_DEL:			// delete story
			delete story;
			story = 0;
			break;
		
		case SST_PRT:
			if(story)
				story->Print();
			break;
		

// --------------------------------------------------------------------- //
//							Novel
// --------------------------------------------------------------------- //
		
		case NOV_MK:				// create a novel
			cout << "Enter novel title: ";
			cin >> tempStr;
			
			if(novel) { delete novel; }
			novel = new Novel_t(tempStr);
			
			tempStr.clear();
			break;
		
		case NOV_ADD:			// add chapter to novel
			i = chooseChap(chaps);
			if(-1==i)
				break;
			
			novel->Add(chaps[i]);
			chaps.erase(chaps.begin()+i);
			
			cout << "novel is now: ";
			novel->Print();
			break;
		
		case NOV_RM:			// remove chapter from novel
			chaps2 = (vector<Chapter_t*>*)(novel->GetChildren());
			
			j = chooseChap(*chaps2);
			if(-1==j)
				break;
			
			novel->Remove((*chaps2)[j]);
			chaps2->clear();
			
			cout << "novel is now: ";
			novel->Print();
			break;
			
		case NOV_DEL:			// delete novel
			delete novel;
			novel = 0;
			break;
		
		case NOV_PRT:
			if(novel)
				novel->Print();
			break;
		
		case MENU:
		
			PrintChoices();
			cout << endl;
			break;
			
		case EXIT:
		default:
		
			goto DELETE_AND_EXIT;
			
		} // end switch
		
		cout << endl;
		cout << "Enter next choice (" << MENU << " for menu, " << EXIT << " to exit): ";
		cin >> choice;
	} // end choice
	
	
	
DELETE_AND_EXIT:

	if(word) { delete word; }
	if(sen) { delete sen; }
	if(ch) { delete ch; }
	if(story) { delete story; }
	if(novel) { delete novel; }
	
	while(!chaps.empty())
	{
		delete(chaps[0]);
		chaps.erase(chaps.begin());
	}
	
	if(chaps2)
	{
		while(!chaps2->empty())
		{
			delete((*chaps2)[0]);
			chaps2->erase(chaps2->begin());
		}
	}
	
	while(!sents.empty())
	{
		delete(sents[0]);
		sents.erase(sents.begin());
	}
	
	if(sents2)
	{
		while(!sents2->empty())
		{
			delete((*sents2)[0]);
			sents2->erase(sents2->begin());
		}
	}
	
	return 0;
}

#endif /* #ifdef _INTERACTIVE */

/*######################################################################*/


