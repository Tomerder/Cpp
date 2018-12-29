#ifndef AMPLIFIER_H
#define AMPLIFIER_H

#include <string>

class Tuner;
class DvdPlayer;
class CdPlayer;

class Amplifier {
public:
    Amplifier(std::string* description);
    void on();
    void off();
    void setStereoSound();
    void setSurroundSound();
    void setVolume(int level);
    void setTuner(Tuner* tuner);
    void setDvd(DvdPlayer* dvd);
    void setCd(CdPlayer* cd);
    std::string toString();
private:
    std::string* m_description;
    Tuner* m_tuner;
    DvdPlayer* m_dvd;
    CdPlayer* m_cd;
    
};

#endif //AMPLIFIER_H
