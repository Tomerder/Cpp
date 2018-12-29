#include <iostream>
#include <string>
#include "amplifier.h"
#include "cd_player.h"
#include "dvd_player.h"
#include "home_theater_facade.h"
#include "projector.h"
#include "popcorn_popper.h"
#include "screen.h"
#include "theater_lights.h"
#include "tuner.h"

using namespace std;

HomeTheaterFacade::HomeTheaterFacade(Amplifier* amp, 
                 Tuner* tuner, 
                 DvdPlayer* dvd, 
                 CdPlayer* cd, 
                 Projector* projector, 
                 Screen* screen,
                 TheaterLights* lights,
                 PopcornPopper* popper) {
 
    m_amp = amp;
    m_tuner = tuner;
    m_dvd = dvd;
    m_cd = cd;
    m_projector = projector;
    m_screen = screen;
    m_lights = lights;
    m_popper = popper;
}
 
void HomeTheaterFacade::watchMovie(string* movie) {
    cout << "Get ready to watch a movie..." << endl;
    m_popper->on();
    m_popper->pop();
    m_lights->dim(10);
    m_screen->down();
    m_projector->on();
    m_projector->wideScreenMode();
    m_amp->on();
    m_amp->setDvd(m_dvd);
    m_amp->setSurroundSound();
    m_amp->setVolume(5);
    m_dvd->on();
    m_dvd->play(movie);
}
 
 
void HomeTheaterFacade::endMovie() {
    cout << "Shutting movie theater down..." << endl;
    m_popper->off();
    m_lights->on();
    m_screen->up();
    m_projector->off();
    m_amp->off();
    m_dvd->stop();
    m_dvd->eject();
    m_dvd->off();
}

void HomeTheaterFacade::listenToCd(string* cdTitle) {
    cout << "Get ready for an audiopile experence..." << endl;
    m_lights->on();
    m_amp->on();
    m_amp->setVolume(5);
    m_amp->setCd(m_cd);
    m_amp->setStereoSound();
    m_cd->on();
    m_cd->play(cdTitle);
}

void HomeTheaterFacade::endCd() {
    cout << "Shutting down CD..." << endl;
    m_amp->off();
    m_amp->setCd(m_cd);
    m_cd->eject();
    m_cd->off();
}

void HomeTheaterFacade::listenToRadio(double frequency) {
    cout << "Tuning in the airwaves..." << endl;
    m_tuner->on();
    m_tuner->setFrequency(frequency);
    m_amp->on();
    m_amp->setVolume(5);
    m_amp->setTuner(m_tuner);
}

void HomeTheaterFacade::endRadio() {
    cout << "Shutting down the tuner..." << endl;
    m_tuner->off();
    m_amp->off();
}

