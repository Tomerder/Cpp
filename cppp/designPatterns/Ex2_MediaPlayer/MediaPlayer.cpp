// MediaPlayer.cpp
//
//	What's this?
//	Author: Vladimir Krapp
//	Created on:
//	Last modified:

#include <iostream>

#include "MediaPlayer.h"

using namespace std;


//============================================================

void MediaPlayerObserver::
Inform(MediaPlayer* _who, PlayerState _newState)
{}


//============================================================

MediaPlayer::MediaPlayer()
    :m_playerState(STOPPED), m_observer(0) 
{}



void MediaPlayer::Play()
{
    if(m_observer)
    {
        m_observer->Inform(this, PLAYING);
    }
    m_playerState = PLAYING;
}

void MediaPlayer::Stop()
{
    if(m_observer)
    {
        m_observer->Inform(this, STOPPED);
    }
    m_playerState = STOPPED;
}

void MediaPlayer::FastForward()
{
    if(m_observer)
    {
        m_observer->Inform(this, FF);
    }
    m_playerState = FF;
}

void MediaPlayer::Rewind()
{
    if(m_observer)
    {
        m_observer->Inform(this, RW);
    }
    m_playerState = RW;
}


PlayerState MediaPlayer::GetState()
{
    return m_playerState;
}

bool MediaPlayer::Attach(MediaPlayerObserver* _observer)
{
    if(m_observer || !_observer)
    {
        return false;
    }

    m_observer = _observer;

    return true;
}

void MediaPlayer::Detach()
{
   m_observer = 0; 
}


//============================================================
DVDPlayer::DVDPlayer()
{}


void DVDPlayer::Play()
{
    MediaPlayer::Play();
    cout << "DVDPlayer::Play()" << endl;
}

void DVDPlayer::Stop()
{
    MediaPlayer::Stop();
    cout << "DVDPlayer::Stop()" << endl;
}

void DVDPlayer::FastForward()
{
    MediaPlayer::FastForward();
    cout << "DVDPlayer::FastForward()" << endl;
}

void DVDPlayer::Rewind()
{
    MediaPlayer::Rewind();
    cout << "DVDPlayer::Rewind()" << endl;
}








//============================================================
VCRPlayer::VCRPlayer()
{}

void VCRPlayer::Play()
{
    MediaPlayer::Play();
    cout << "VCRPlayer::Play()" << endl;
}

void VCRPlayer::Stop()
{
    MediaPlayer::Stop();
    cout << "VCRPlayer::Stop()" << endl;
}

void VCRPlayer::FastForward()
{
    MediaPlayer::FastForward();
    cout << "VCRPlayer::FastForward()" << endl;
}

void VCRPlayer::Rewind()
{
    MediaPlayer::Rewind();
    cout << "VCRPlayer::Rewind()" << endl;
}









//============================================================
CDPlayer::CDPlayer()
{}

void CDPlayer::Play()
{
    MediaPlayer::Play();
    cout << "CDPlayer::Play()" << endl;
}

void CDPlayer::Stop()
{
    MediaPlayer::Stop();
    cout << "CDPlayer::Stop()" << endl;
}

void CDPlayer::FastForward()
{
    MediaPlayer::FastForward();
    cout << "CDPlayer::FastForward()" << endl;
}

void CDPlayer::Rewind()
{
    MediaPlayer::Rewind();
    cout << "CDPlayer::Rewind()" << endl;
}


