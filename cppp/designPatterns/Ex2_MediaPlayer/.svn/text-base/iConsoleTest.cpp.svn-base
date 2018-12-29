#include <iostream>
using namespace std;

#include "MediaPlayer.h"
#include "EntConsole.h"	


EntConsole g_ec;

MediaPlayer* PlayerSelect()
{
    int ch = 0;
    cout << "Select player:" << endl;
    cout << "1 - DVD:" << endl;
    cout << "2 - VCR:" << endl;
    cout << "3 - CD:" << endl;

    cin >> ch;

    cout << endl;

    switch(ch)
    {
        case 1:
            return g_ec.m_dvd;
        case 2:
            return g_ec.m_vcr;
        case 3:
            return g_ec.m_cd;
        default:
            return 0;
    }
    return 0;
}

void play()
{
    MediaPlayer* player = PlayerSelect();
    if(!player)
    {
        cout << "Invalid player selected, returning to menu" << endl;
        return;
    }

    player->Play();
}

void stop()
{
    MediaPlayer* player = PlayerSelect();
    if(!player)
    {
        cout << "Invalid player selected, returning to menu" << endl;
        return;
    }

    player->Stop();
}

void ff()
{
    MediaPlayer* player = PlayerSelect();
    if(!player)
    {
        cout << "Invalid player selected, returning to menu" << endl;
        return;
    }

    player->FastForward();
}

void rw()
{
    MediaPlayer* player = PlayerSelect();
    if(!player)
    {
        cout << "Invalid player selected, returning to menu" << endl;
        return;
    }

    player->Rewind();
}

int main() {

	int cont=1;
	int ch  =0;
	
	while(cont) {
        cout << endl;
		cout << "1 - Play " 	<< endl;
		cout << "2 - Stop " 	<< endl;
		cout << "3 - Fast Forward "	<< endl;
		cout << "4 - Rewind "	<< endl;
		cout << "Any other - exit "	<< endl;
		
		cout << " Please, choose option: ";
	
		cin >> ch;

        cout << endl;

		switch(ch) {
			case 1 : play(); break;			
			case 2 : stop(); break;			
			case 3 : ff(); break;
			case 4 : rw(); break;
			default: cont = 0;
		}
	}

	return 0;
}



