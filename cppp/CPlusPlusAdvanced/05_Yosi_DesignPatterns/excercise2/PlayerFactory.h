/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-06    
    Last modified date:		2013-11-06
    Description: 	
****************************************************************************/

#ifndef __PLAYER_FACTORY_H__
#define __PLAYER_FACTORY_H__

#include "BiduritEnums.h"
#include "Players.h"


//=========================================================================
// 							Abstract Factory
//=========================================================================
class PlayerFactory_t
{
public:
	virtual  PlayerDevice_t*	MakePlayer() = 0;
};
//=========================================================================


//-------------------------------------------------------------------------
// 								CD Factory
//-------------------------------------------------------------------------
class CDFactory_t : public PlayerFactory_t
{
public:
	virtual  PlayerDevice_t*	MakePlayer()
	{
		return new CDPlayer_t;
	}
};
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
// 								DVD Factory
//-------------------------------------------------------------------------
class DVDFactory_t : public PlayerFactory_t
{
public:
	virtual  PlayerDevice_t*	MakePlayer()
	{
		return new DVDPlayer_t;
	}
};
//-------------------------------------------------------------------------


//-------------------------------------------------------------------------
// 								VCR Factory
//-------------------------------------------------------------------------
class VCRFactory_t : public PlayerFactory_t
{
public:
	virtual  PlayerDevice_t*	MakePlayer()
	{
		return new VCRPlayer_t;
	}
};
//-------------------------------------------------------------------------


#endif  /* __PLAYER_FACTORY_H__ */
