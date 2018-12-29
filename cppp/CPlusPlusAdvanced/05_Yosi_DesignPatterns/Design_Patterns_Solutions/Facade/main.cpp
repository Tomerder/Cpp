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

int main() {
    Amplifier* amp = new Amplifier(new string("Top-O-Line Amplifier"));
    Tuner* tuner = new Tuner(new string("Top-O-Line AM/FM Tuner"), amp);
    DvdPlayer* dvd = new DvdPlayer(new string("Top-O-Line DVD Player"), amp);
    CdPlayer* cd = new CdPlayer(new string("Top-O-Line CD Player"), amp);
    Projector* projector = new Projector(new string("Top-O-Line Projector"), dvd);
    TheaterLights* lights = new TheaterLights(new string("Theater Ceiling Lights"));
    Screen* screen = new Screen(new string("Theater Screen"));
    PopcornPopper* popper = new PopcornPopper(new string("Popcorn Popper"));
    
    HomeTheaterFacade* homeTheater = new HomeTheaterFacade(amp, tuner, dvd, cd, projector, screen, lights, popper);
    
    homeTheater->watchMovie(new string("Raiders of the Lost Ark"));
    homeTheater->endMovie();
}
