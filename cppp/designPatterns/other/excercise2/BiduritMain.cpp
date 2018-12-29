/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-00-00    
    Last modified date:		2013-00-00
    Description: 	
****************************************************************************/

#include <iostream>

#include "BiduritEnums.h"
#include "Players.h"
#include "PlayerFactory.h"
#include "Bidurit.h"

using namespace std;


enum Choices
{
	EXIT,
	
	ADD_CD,
	ADD_DVD,
	ADD_VCR,
	RM_CD,
	RM_DVD,
	RM_VCR,
	PLAY_CD,
	PLAY_DVD,
	PLAY_VCR,
	PAUSE_CD,
	PAUSE_DVD,
	PAUSE_VCR,
	FORE_CD,
	FORE_DVD,
	FORE_VCR,
	REWIND_CD,
	REWIND_DVD,
	REWIND_VCR,
	
	MENU = 100
};


// print choices
void PrintChoices(void)
{
	cout << endl;
	cout << "Add Player to bidurit: CD - " << ADD_CD << ", DVD: " << ADD_DVD << ", VCR: " << ADD_VCR << endl;
	cout << "Disconnect Player from bidurit: CD - " << RM_CD << ", DVD: " << RM_DVD << ", VCR: " << RM_VCR << endl;
	cout << "Play: CD - " << PLAY_CD << ", DVD: " << PLAY_DVD << ", VCR: " << PLAY_VCR << endl;
	cout << "Pause: CD - " << PAUSE_CD << ", DVD: " << PAUSE_DVD << ", VCR: " << PAUSE_VCR << endl;
	cout << "Foreward: CD - " << FORE_CD << ", DVD: " << FORE_DVD << ", VCR: " << FORE_VCR << endl;
	cout << "Rewind: CD - " << REWIND_CD << ", DVD: " << REWIND_DVD << ", VCR: " << REWIND_VCR << endl;

	cout << "Print menu: " << MENU << endl;
	cout << "Exit: " << EXIT << endl;
}
/*======================================================================*/




/*======================================================================*/
//								MAIN
/*======================================================================*/
int main()
{
	int choice;
	Bidurit_t B;
	
	PlayerFactory_t* CDF =  new CDFactory_t;
	PlayerFactory_t* DVDF = new DVDFactory_t;
	PlayerFactory_t* VCRF = new VCRFactory_t;
			
	PlayerDevice_t* cd = CDF->MakePlayer();
	PlayerDevice_t* dvd = DVDF->MakePlayer();
	PlayerDevice_t* vcr = VCRF->MakePlayer();
	
	
	PrintChoices();
	
	cout << endl << "Enter your choice: ";
	cin >> choice;
	
	while(choice)
	{
		
		switch(choice)
		{
		// ------------ add -------------/
		case ADD_CD:
			try {
				B.AddPlayer(cd);
			}
			catch(const char* _exep) {
				cout << _exep << endl;
				break;
			}
			cout << "CD player added" << endl;
			break;
		
		case ADD_DVD:
			try {
				B.AddPlayer(dvd);
			}
			catch(const char* _exep) {
				cout << _exep << endl;
				break;
			}
			cout << "DVD player added" << endl;
			break;
		
		case ADD_VCR:
			try {
				B.AddPlayer(vcr);
			}
			catch(const char* _exep) {
				cout << _exep << endl;
				break;
			}
			cout << "VCR player added" << endl;
			break;
		
		// ------------ disconnect -------------/
		case RM_CD:
			try {
				B.DisconnectPlayer(CD);
			}
			catch(const char* _exep) {
				cout << _exep << endl;
				break;
			}
			
			cout << "CD player disconnected" << endl;
			break;
		
		case RM_DVD:
			try {
				B.DisconnectPlayer(DVD);
			}
			catch(const char* _exep) {
				cout << _exep << endl;
				break;
			}
			
			cout << "DVD player disconnected" << endl;
			break;
		
		case RM_VCR:
			try {
				B.DisconnectPlayer(VCR);
			}
			catch(const char* _exep) {
				cout << _exep << endl;
				break;
			}
			
			cout << "VCR player disconnected" << endl;
			break;
		
		// ------------ play -------------/
		
		case PLAY_CD:
			try {
				B.PlayerPlay(cd);
			}
			catch(const char* _exep) {
				cout << _exep << endl;
			}
			break;
		
		case PLAY_DVD:
			try {
				B.PlayerPlay(dvd);
			}
			catch(const char* _exep) {
				cout << _exep << endl;
			}
			break;
		
		case PLAY_VCR:
			try {
				B.PlayerPlay(vcr);
			}
			catch(const char* _exep) {
				cout << _exep << endl;
			}
			break;
		
		// ------------ pause -------------/
		
		case PAUSE_CD:
			try {
				B.PlayerPause(cd);
			}
			catch(const char* _exep) {
				cout << _exep << endl;
			}
			break;
		
		case PAUSE_DVD:
			try {
				B.PlayerPause(dvd);
			}
			catch(const char* _exep) {
				cout << _exep << endl;
			}
			break;
		
		case PAUSE_VCR:
			try {
				B.PlayerPause(vcr);
			}
			catch(const char* _exep) {
				cout << _exep << endl;
			}
			break;
		
		// ------------ foreward -------------/
		
		case FORE_CD:
			try {
				B.PlayerForeward(cd);
			}
			catch(const char* _exep) {
				cout << _exep << endl;
			}
			break;
		
		case FORE_DVD:
			try {
				B.PlayerForeward(dvd);
			}
			catch(const char* _exep) {
				cout << _exep << endl;
			}
			break;
		
		case FORE_VCR:
			try {
				B.PlayerForeward(vcr);
			}
			catch(const char* _exep) {
				cout << _exep << endl;
			}
			break;
		
		// ------------ rewind -------------/
		
		case REWIND_CD:
			try {
				B.PlayerRewind(cd);
			}
			catch(const char* _exep) {
				cout << _exep << endl;
			}
			break;
		
		case REWIND_DVD:
			try {
				B.PlayerRewind(dvd);
			}
			catch(const char* _exep) {
				cout << _exep << endl;
			}
			break;
		
		case REWIND_VCR:
			try {
				B.PlayerRewind(vcr);
			}
			catch(const char* _exep) {
				cout << _exep << endl;
			}
			break;
		
		case MENU:
		
			PrintChoices();
			cout << endl;
			break;
			
		case EXIT:
		default:
			goto DELETE_AND_EXIT;
			
		} // end switch
		
		cout << "Enter next choice (" << MENU << " for menu, " << EXIT << " to exit): ";
		cin >> choice;
	} // end choice


DELETE_AND_EXIT:
	
	CDPlayer_t* cd2 = static_cast<CDPlayer_t*>(cd);
	DVDPlayer_t* dvd2 = static_cast<DVDPlayer_t*>(dvd);
	VCRPlayer_t* vcr2 = static_cast<VCRPlayer_t*>(vcr);
	
	delete cd2;
	delete dvd2;
	delete vcr2;
	
	return 0;
}
/*######################################################################*/

