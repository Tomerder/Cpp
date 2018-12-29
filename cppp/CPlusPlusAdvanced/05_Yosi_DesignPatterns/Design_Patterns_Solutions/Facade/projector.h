#ifndef PROJECTOR_H
#define PROJECTOR_H

#include <string>

class DvdPlayer;

class Projector {
public:
    Projector(std::string* description, DvdPlayer* dvdPlayer);
    void on();
    void off();
    void wideScreenMode();
    void tvMode();
    std::string toString();
private:
    std::string* m_description;
    DvdPlayer* m_dvdPlayer;
};

#endif //PROJECTOR_H
