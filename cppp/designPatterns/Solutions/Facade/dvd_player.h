#ifndef DVD_PLAYER_H
#define DVD_PLAYER_H

#include <string>

class Amplifier;

class DvdPlayer {
public:    
    DvdPlayer(std::string* description, Amplifier* amplifier);
    void on();
    void off();
    void eject();
    void play(std::string* movie);
    void play(int track);
    void stop();
    void pause();
    void setTwoChannelAudio();
    void setSurroundAudio();
    std::string toString();
private:
    std::string* m_description;
    int m_currentTrack;
    Amplifier* m_amplifier;
    std::string* m_movie;  
};

#endif //DVD_PLAYER_H
