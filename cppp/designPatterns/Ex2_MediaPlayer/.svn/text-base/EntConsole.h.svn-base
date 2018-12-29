// EntConsole.h
//
//	Entertainment console class
//	Author: Vladimir Krapp
//	Created on: 25/3/14
//	Last modified:

#ifndef __ENT_CONSOLE_H__
#define __ENT_CONSOLE_H__

#include "MediaPlayer.h"
#include "PlayerFactory.h"
#include "Memento.h"


class Mediator
{
    public:
        virtual ~Mediator() = 0;
        
 //   private:

};

struct EntConsoleState : public MementoState
{
    PlayerState m_dvdState;
    PlayerState m_vcrState;
    PlayerState m_cdState;
};

class EntConsoleMemento;

class EntConsole : public Mediator, public MediaPlayerObserver, public Originator
{
    public:

        EntConsole();
        ~EntConsole();


        MediaPlayer* m_dvd;
        MediaPlayer* m_vcr;
        MediaPlayer* m_cd;
       

    // MediaPlayerObserver functions   
        virtual void Inform(MediaPlayer* _who, PlayerState _newState);

    // Originator functions
       virtual Memento* GetMemento(){return 0;};
       virtual bool     RestoreState(const Memento* _mem){return true;};

    private:
        MediaPlayer* m_nowPlaying;

};

class EntConsoleMemento : public Memento
{
    public:

        virtual ~EntConsoleMemento(){};
        virtual void Print(){};

    friend class EntConsole;

    private:
        
        EntConsoleMemento(){};
        EntConsoleMemento(EntConsoleState);

        EntConsoleState m_state;
};


#endif //__ENT_CONSOLE_H__
