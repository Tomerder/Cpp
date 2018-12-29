// EntConsole.cpp
//
//	What's this?
//	Author: Vladimir Krapp
//	Created on:
//	Last modified:

#include "EntConsole.h"

Mediator::~Mediator() 
{}

//============================================================
EntConsole::EntConsole()
    :m_nowPlaying(0)
{
    m_dvd = PlayerFactory::Fabricate(DVD);
    m_dvd->Attach(this);

    m_vcr = PlayerFactory::Fabricate(VCR);
    m_vcr->Attach(this);

    m_cd = PlayerFactory::Fabricate(CD);
    m_cd->Attach(this);
}

EntConsole::~EntConsole()
{
    
}


void EntConsole::Inform(MediaPlayer* _who, PlayerState _newState)
{
    if(_newState == PLAYING)
    {
        if(m_nowPlaying && (_who != m_nowPlaying))
        {
            m_nowPlaying->Stop();
        }
        m_nowPlaying = _who;
    }
    // + update state logger
}
//============================================================

EntConsoleMemento::EntConsoleMemento(EntConsoleState _state)
{
    m_state = _state;
}





