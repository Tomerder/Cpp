/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-06    
    Last modified date:		2013-11-06
    Description: 	
****************************************************************************/

#ifndef __PLAYERS_H__
#define __PLAYERS_H__

#include "BiduritEnums.h"

class PlayerFactory_t;

//=========================================================================
// 							Abstract Player
//=========================================================================
class PlayerDevice_t
{
public:
	PlayerDevice_t(PlayerType _type) : m_type(_type) { m_status = PAUSED; }
	
	virtual void Play () = 0;
	virtual void Pause () = 0;
	virtual void Foreward () = 0;
	virtual void Rewind () = 0;
	
	PlayerStatus GetStatus() const { return m_status; }
	PlayerType   GetType() const   { return m_type; }
	
protected:
	PlayerStatus m_status;
	PlayerType	 m_type;
	
};
//=========================================================================



//-------------------------------------------------------------------------
// 					CD Player - template in manufactorer?
//-------------------------------------------------------------------------
class CDPlayer_t : public PlayerDevice_t
{
public:
	
	friend class CDFactory_t;
	
	virtual ~CDPlayer_t() {};
	
	virtual void Play();
	virtual void Pause();
	virtual void Foreward();
	virtual void Rewind();
	
	//inherited:
//	PlayerStatus	m_status;
//	PlayerType		m_type;

private:
	CDPlayer_t() : PlayerDevice_t(CD) {}
};

//-------------------------------------------------------------------------
// 					DVD Player - template in manufactorer?
//-------------------------------------------------------------------------


class DVDPlayer_t : public PlayerDevice_t
{
public:
	
	friend class DVDFactory_t;
	
	virtual ~DVDPlayer_t() {};
	
	virtual void Play();
	virtual void Pause();
	virtual void Foreward();
	virtual void Rewind();
	
		//inherited:
//	PlayerStatus 	m_status;
//	PlayerType		m_type;

private:
	DVDPlayer_t() : PlayerDevice_t(DVD) {}
};

//-------------------------------------------------------------------------
// 					VCR Player - template in manufactorer?
//-------------------------------------------------------------------------


class VCRPlayer_t : public PlayerDevice_t
{
public:
	friend class VCRFactory_t;
	
	virtual ~VCRPlayer_t() {};
	
	virtual void Play();
	virtual void Pause();
	virtual void Foreward();
	virtual void Rewind();
	
		//inherited:
//	PlayerStatus 	m_status;
//	PlayerType		m_type;
private:
	VCRPlayer_t() : PlayerDevice_t(VCR) {}
};


#endif  /* __PLAYERS_H__ */
