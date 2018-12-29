#ifndef HOME_THEATER_FACADE_H
#define HOME_THEATER_FACADE_H

class Amplifier;
class Tuner;
class DvdPlayer;
class CdPlayer;
class Projector;
class Screen;
class TheaterLights;
class PopcornPopper;

class HomeTheaterFacade {
public:
    HomeTheaterFacade(Amplifier* amp, 
                 Tuner* tuner, 
                 DvdPlayer* dvd, 
                 CdPlayer* cd, 
                 Projector* projector, 
                 Screen* screen,
                 TheaterLights* lights,
                 PopcornPopper* popper);
    void watchMovie(std::string* movie);
    void endMovie();
    void listenToCd(std::string* cdTitle);
    void endCd();
    void listenToRadio(double frequency);
    void endRadio();
private:
    Amplifier* m_amp;
    Tuner* m_tuner;
    DvdPlayer* m_dvd;
    CdPlayer* m_cd;
    Projector* m_projector;
    TheaterLights* m_lights;
    Screen* m_screen;
    PopcornPopper* m_popper;
};

#endif //HOME_THEATER_FACADE_H
