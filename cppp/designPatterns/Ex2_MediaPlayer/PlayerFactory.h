// PlayerFactory.h
//
//	Media Player Abstract Factory Class
//	Author: Vladimir Krapp
//	Created on: 25/3/14
//	Last modified:

#ifndef __PLAYER_FACTORY_H__
#define __PLAYER_FACTORY_H__

#include <vector>

#include "MediaPlayer.h"



class PlayerFactory
{
    public:
        static MediaPlayer* Fabricate(const PlayerType& _type);
        
        virtual ~PlayerFactory() = 0;

    private:
        static MediaPlayer* FabricateVideoPlayer(const PlayerType& _type);
        static MediaPlayer* FabricateDVDPlayer();
        static MediaPlayer* FabricateVCRPlayer();

        static MediaPlayer* FabricateAudioPlayer(const PlayerType& _type);
        static MediaPlayer* FabricateCDPlayer();
    

    private:
        static std::vector<MediaPlayer*> s_players;
};



#endif //__PLAYER_FACTORY_H__
