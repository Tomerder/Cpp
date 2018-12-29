#ifndef CD_PLAYER_H
#define CD_PLAYER_H

#include <string>

class Amplifier;

class CdPlayer {
public:
    CdPlayer(std::string* description, Amplifier* amplifier);
    void on();
    void off();
    void eject();
    void play(std::string* title);
    void play(int track);
    void stop();
    void pause();
    std::string toString();
private:
    std::string* m_description;
    int m_currentTrack;
    Amplifier* m_amplifier;
    std::string* m_title;  
};

#endif //CD_PLAYER_H
