// PlayerFactory.cpp
//
//	What's this?
//	Author: Vladimir Krapp
//	Created on:
//	Last modified:

#include "PlayerFactory.h"

using namespace std;

vector<MediaPlayer*> PlayerFactory::s_players;


MediaPlayer* PlayerFactory::Fabricate(const PlayerType& _type)
{
    MediaPlayer* player = 0;

    switch(_type)
    {
        case DVD:
        case VCR:
            player = FabricateVideoPlayer(_type);
            break;

        case CD:
            player = FabricateAudioPlayer(_type);
            break;

        default:
             break;
    }
    
    if(player)
    {
        s_players.push_back(player);
    }

    return player;
}

 MediaPlayer* PlayerFactory::FabricateVideoPlayer(const PlayerType& _type)
{
    MediaPlayer* player = 0;

    switch (_type)
    {
        case DVD:
            player = FabricateDVDPlayer();
            break;

        case VCR:
            player = FabricateVCRPlayer();
            break;

        default:
            break;
    }

    return player;
}

 MediaPlayer* PlayerFactory::FabricateDVDPlayer()
{
    return new DVDPlayer;
}

 MediaPlayer* PlayerFactory::FabricateVCRPlayer()
{
    return new VCRPlayer;
}

//============================================================
 MediaPlayer* PlayerFactory::FabricateAudioPlayer(const PlayerType& _type)
{
    MediaPlayer* player = 0;

    switch (_type)
    {
        case CD:
            player = FabricateCDPlayer();
            break;

        default:
            break;
    }

    return player;
}


 MediaPlayer* PlayerFactory::FabricateCDPlayer()
{
    return new CDPlayer;
}

