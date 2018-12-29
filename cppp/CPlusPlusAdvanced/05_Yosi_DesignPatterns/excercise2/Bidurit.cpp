/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-06    
    Last modified date:		2013-11-06
    Description: 	
****************************************************************************/

#include <vector>
#include <algorithm>

#include "PlayerFactory.h"
#include "Players.h"
#include "Bidurit.h"

using namespace std;


// CTOR
Bidurit_t::Bidurit_t()
{
	m_curPlaying = 0;
}
//=========================================================================

// DTOR
Bidurit_t::~Bidurit_t()
{
	m_players.clear();
}
//=========================================================================

// add player to console
void Bidurit_t::AddPlayer	(PlayerDevice_t* _p)
{
	if( IsConnected(_p) )
	{
		throw "Device is already connected to bidurit";
	}
	m_players.push_back(_p);
}
//=========================================================================


// functor for GetPlayer
class FindType
{
public:
	explicit FindType(PlayerType _type) : m_type(_type) {}
	int operator ()(PlayerDevice_t* _p)
	{
		return (_p->GetType() == m_type);
	}
	
private:
	PlayerType m_type;
};

// get 1st player of given type 
PlayerDevice_t* Bidurit_t::DisconnectPlayer(PlayerType _type)
{
	if(m_players.empty())
	{
		throw "No devices currently connected";
	}
	
	vector<PlayerDevice_t*>::iterator itr;
	itr = find_if(m_players.begin(), m_players.end(), FindType(_type));
	
	if(m_players.end() == itr)
	{
		throw "No device of this type is connected";
	}
	
	PlayerDevice_t* player = *itr;
	
	if( player == m_curPlaying )
	{
		PlayerPause(player);
	}
	
	m_players.erase(itr);
	
	return player;
}
//=========================================================================



void Bidurit_t::PlayerPlay		(PlayerDevice_t* _p)
{
	if(!_p)
	{
		throw "Received NULL pointer!";
	}
	if( !IsConnected(_p) )
	{
		throw "Device is not connected to bidurit";
	}
	
	if( m_curPlaying )
	{
		if(m_curPlaying == _p)
		{
			throw "Device is already playing";
		}
		m_curPlaying->Pause();
	}
	m_curPlaying = _p;
	_p->Play();
}
//=========================================================================

void Bidurit_t::PlayerPause	(PlayerDevice_t* _p)
{
	if(!_p)
	{
		throw "Received NULL pointer!";
	}
	if( !IsConnected(_p) )
	{
		throw "Device is not connected to bidurit";
	}
	
	if( _p == m_curPlaying )
	{
		m_curPlaying = 0;
		_p->Pause();
	}
}
//=========================================================================

void Bidurit_t::PlayerForeward	(PlayerDevice_t* _p)
{
	if(!_p)
	{
		throw "Received NULL pointer!";
	}
	if( !IsConnected(_p) )
	{
		throw "Device is not connected to bidurit";
	}
	
	if( _p == m_curPlaying )
	{
		m_curPlaying = 0;
	}
	_p->Foreward();
}
//=========================================================================

void Bidurit_t::PlayerRewind	(PlayerDevice_t* _p)
{
	if(!_p)
	{
		throw "Received NULL pointer!";
	}
	if( !IsConnected(_p) )
	{
		throw "Device is not connected to bidurit";
	}
	
	if( _p == m_curPlaying )
	{
		m_curPlaying = 0;
	}
	_p->Rewind();
}
//=========================================================================



