#include <iostream>
#include <string>
#include "dvd_player.h"

using namespace std;

DvdPlayer::DvdPlayer(string* description, Amplifier* amplifier) {
    m_description = description;
    m_amplifier = amplifier;
}

void DvdPlayer::on() {
    cout << *m_description << " on" << endl;
}

void DvdPlayer::off() {
    cout << *m_description << " off" << endl;
}

void DvdPlayer::eject() {
    m_movie = 0;
    cout << *m_description << " eject" << endl;
}

void DvdPlayer::play(string* movie) {
    m_movie = movie;
    m_currentTrack = 0;
    cout << *m_description << " playing \"" << *m_movie << "\"" << endl;
}

void DvdPlayer::play(int track) {
    if (m_movie == 0) {
        cout << *m_description << " can't play track " << m_currentTrack << ", no dvd inserted" << endl;
    } else {
        m_currentTrack = track;
        cout << *m_description << " playing track " << m_currentTrack << " of \"" << *m_movie << endl;
    }
}

void DvdPlayer::stop() {
    m_currentTrack = 0;
    cout << *m_description << " stopped \"" << *m_movie << "\"" << endl;
}

void DvdPlayer::pause() {
    cout << *m_description << " paused \"" << *m_movie << "\"" << endl;
}

void DvdPlayer::setTwoChannelAudio() {
    cout << *m_description << " set two channel audio" << endl;
}
    
void DvdPlayer::setSurroundAudio() {
    cout << *m_description << " set surround audio" << endl;
}

string DvdPlayer::toString() {
    return *m_description;
}
