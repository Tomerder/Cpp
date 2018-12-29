/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-06    
    Last modified date:		2013-11-06
    Description: 	
****************************************************************************/

#include <iostream>

#include "Bidurit.h"
#include "Players.h"

using namespace std;


//=======================================================================//
//							ABSTRACT PLAYER FUNCTIONS
//=======================================================================//

void PlayerDevice_t::Play()
{
	m_status = PLAYING;
}
//-------------------------------------------------------------------------

void PlayerDevice_t::Pause()
{
	m_status = PAUSED;
}
//-------------------------------------------------------------------------

void PlayerDevice_t::Foreward()
{
	m_status = FOREWARD;
}
//-------------------------------------------------------------------------

void PlayerDevice_t::Rewind()
{
	m_status = REWIND;
}
//-------------------------------------------------------------------------


//=======================================================================//
//							CD PLAYER FUNCTIONS
//=======================================================================//

void CDPlayer_t::Play()
{
	PlayerDevice_t::Play();
	cout << "CD: Play" << endl;
}
//-------------------------------------------------------------------------

void CDPlayer_t::Pause()
{
	PlayerDevice_t::Pause();
	cout << "CD: Pause" << endl;
}
//-------------------------------------------------------------------------

void CDPlayer_t::Foreward()
{
	PlayerDevice_t::Foreward();
	cout << "CD: Foreward" << endl;
}
//-------------------------------------------------------------------------

void CDPlayer_t::Rewind()
{
	PlayerDevice_t::Rewind();
	cout << "CD: Rewind" << endl;
}
//-------------------------------------------------------------------------


//=======================================================================//
//							DVD PLAYER FUNCTIONS
//=======================================================================//

void DVDPlayer_t::Play()
{
	PlayerDevice_t::Play();
	cout << "DVD: Play" << endl;
}
//-------------------------------------------------------------------------

void DVDPlayer_t::Pause()
{
	PlayerDevice_t::Pause();
	cout << "DVD: Pause" << endl;
}
//-------------------------------------------------------------------------

void DVDPlayer_t::Foreward()
{
	PlayerDevice_t::Foreward();
	cout << "DVD: Foreward" << endl;
}
//-------------------------------------------------------------------------

void DVDPlayer_t::Rewind()
{
	PlayerDevice_t::Rewind();
	cout << "DVD: Rewind" << endl;
}
//-------------------------------------------------------------------------

//=======================================================================//
//							VCR PLAYER FUNCTIONS
//=======================================================================//

void VCRPlayer_t::Play()
{
	PlayerDevice_t::Play();
	cout << "VCR: Play" << endl;
}
//-------------------------------------------------------------------------

void VCRPlayer_t::Pause()
{
	PlayerDevice_t::Pause();
	cout << "VCR: Pause" << endl;
}
//-------------------------------------------------------------------------

void VCRPlayer_t::Foreward()
{
	PlayerDevice_t::Foreward();
	cout << "VCR: Foreward" << endl;
}
//-------------------------------------------------------------------------

void VCRPlayer_t::Rewind()
{
	PlayerDevice_t::Rewind();
	cout << "VCR: Rewind" << endl;
}
//-------------------------------------------------------------------------


