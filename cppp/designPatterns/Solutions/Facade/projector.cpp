#include <iostream>
#include <string>
#include "projector.h"
#include "dvd_player.h"

using namespace std;

Projector::Projector(string* description, DvdPlayer* dvdPlayer) {
    m_description = description;
    m_dvdPlayer = dvdPlayer;
}

void Projector::on() {
    cout << *m_description << " on" << endl;
}

void Projector::off() {
    cout << *m_description << " off" << endl;
}

void Projector::wideScreenMode() {
    cout << *m_description << " in widescreen mode (16x9 aspect ratio)" << endl;
}

void Projector::tvMode() {
    cout << *m_description << " in tv mode (4x3 aspect ratio)" << endl;
}

string Projector::toString() {
    return *m_description;
}
