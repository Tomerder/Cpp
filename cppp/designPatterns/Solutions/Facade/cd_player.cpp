#include <iostream>
#include <string>
#include "cd_player.h"

using namespace std;

CdPlayer::CdPlayer(string* description, Amplifier* amplifier) {
    m_description = description;
    m_amplifier = amplifier;
}

void CdPlayer::on() {
    cout << *m_description << " on" << endl;
}

void CdPlayer::off() {
    cout << *m_description << " off" << endl;
}

void CdPlayer::eject() {
    m_title = 0;
    cout << *m_description << " eject" << endl;
}

void CdPlayer::play(string* title) {
    m_title = title;
    m_currentTrack = 0;
    cout << *m_description << " playing \"" << m_title << "\"" << endl;
}

void CdPlayer::play(int track) {
    if (m_title == 0) {
        cout << *m_description << " can't play track " << m_currentTrack << ", no cd inserted" << endl;
    } else {
        m_currentTrack = track;
        cout << *m_description << " playing track " << m_currentTrack << endl;
    }
}

void CdPlayer::stop() {
    m_currentTrack = 0;
    cout << *m_description << " stopped" << endl;
}

void CdPlayer::pause() {
    cout << *m_description << " paused \"" << *m_title << "\"" << endl;
}

string CdPlayer::toString() {
    return *m_description;
}
