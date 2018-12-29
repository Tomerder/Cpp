#include <iostream>
#include <string>
#include "amplifier.h"
#include "tuner.h"
#include "dvd_player.h"
#include "cd_player.h"

using namespace std;

Amplifier::Amplifier(string* description) {
    m_description = description;
}

void Amplifier::on() {
    cout << *m_description << " on" << endl;
}

void Amplifier::off() {
    cout << *m_description << " off" << endl;
}

void Amplifier::setStereoSound() {
    cout << *m_description << " stereo mode on" << endl;
}

void Amplifier::setSurroundSound() {
    cout << *m_description << " surround sound on (5 speakers, 1 subwoofer)" << endl;
}

void Amplifier::setVolume(int level) {
    cout << *m_description << " setting volume to " << level << endl;
}

void Amplifier::setTuner(Tuner* tuner) {
    cout << *m_description << " setting tuner to " << tuner->toString() << endl;
    m_tuner = tuner;
}

void Amplifier::setDvd(DvdPlayer* dvd) {
    cout << *m_description << " setting DVD player to " << dvd->toString() << endl;
    m_dvd = dvd;
}

void Amplifier::setCd(CdPlayer* cd) {
    cout << *m_description << " setting CD player to " << cd->toString() << endl;
    m_cd = cd;
}

string Amplifier::toString() {
    cout << "I am here: " << *m_description << endl;
    return *m_description;
}
