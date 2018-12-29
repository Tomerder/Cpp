// MediaPlayer.h
//
//	MediaPlayer abstract class (interface)
//	Author: Vladimir Krapp
//	Created on: 24/3/14
//	Last modified:

#ifndef __MEDIA_PLAYER_H__
#define __MEDIA_PLAYER_H__

//============================================================

typedef enum {STOPPED, PLAYING, FF, RW} PlayerState;

class MediaPlayerObserver;

class MediaPlayer // Abstract Interface
{
    public:
        
        MediaPlayer();

        virtual void Play() = 0;
        virtual void Stop() = 0;
        virtual void FastForward() = 0;
        virtual void Rewind() = 0;

        PlayerState GetState();

        bool Attach(MediaPlayerObserver* _observer);
        void Detach();
    protected:

    private:

        PlayerState m_playerState;

        MediaPlayerObserver* m_observer;
};


class MediaPlayerObserver
{
    public:
        virtual void Inform(MediaPlayer* _who, PlayerState _newState) = 0;
};

//============================================================

typedef enum {DVD, VCR, CD} PlayerType;


class PlayerFactory;

class DVDPlayer : public MediaPlayer
{
    friend class PlayerFactory;

    public:
        virtual ~DVDPlayer(){};

        virtual void Play();
        virtual void Stop();
        virtual void FastForward();
        virtual void Rewind();

    private:
        DVDPlayer();
};

class VCRPlayer : public MediaPlayer
{
    friend class PlayerFactory;

    public:
        virtual ~VCRPlayer(){};

        virtual void Play();
        virtual void Stop();
        virtual void FastForward();
        virtual void Rewind();

    private:
        VCRPlayer();
};

class CDPlayer : public MediaPlayer
{
    friend class PlayerFactory;

    public:
        virtual ~CDPlayer(){};

        virtual void Play();
        virtual void Stop();
        virtual void FastForward();
        virtual void Rewind();
    
    private:
        CDPlayer();
};



//============================================================
#endif //__MEDIA_PLAYER_H__
