/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-06    
    Last modified date:		2013-11-06
    Description: 	
****************************************************************************/

#ifndef __BIDURIT_H__
#define __BIDURIT_H__

#include <vector>
#include <algorithm>

#include "BiduritEnums.h"

class PlayerDevice_t;


//=========================================================================
// 				Bidurit - an entertainment console (mediator)
//=========================================================================
class Bidurit_t
{
public:
	explicit Bidurit_t();
	virtual ~Bidurit_t();
	
		PlayerDevice_t* DisconnectPlayer	(PlayerType _type);
		void 			AddPlayer			(PlayerDevice_t* _p);
	
	virtual void PlayerPlay		(PlayerDevice_t* _p);
	virtual void PlayerPause	(PlayerDevice_t* _p);
	virtual void PlayerForeward	(PlayerDevice_t* _p);
	virtual void PlayerRewind	(PlayerDevice_t* _p);
	
private:
	std::vector<PlayerDevice_t*> m_players;
	PlayerDevice_t* m_curPlaying;
	
	inline bool IsConnected(PlayerDevice_t* _p);
	
	// no copy
	Bidurit_t(const Bidurit_t& _b);
	Bidurit_t& operator =(const Bidurit_t& _b);
};
//=========================================================================


inline bool Bidurit_t::IsConnected(PlayerDevice_t* _p)
{
	return ( m_players.end() != find(m_players.begin(), m_players.end(), _p) );
}
//=========================================================================


#endif /* __BIDURIT_H__ */
