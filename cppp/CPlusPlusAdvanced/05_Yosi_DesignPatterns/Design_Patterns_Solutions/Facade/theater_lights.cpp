#include <iostream>
#include <string>
#include "theater_lights.h"

using namespace std;

TheaterLights::TheaterLights(string* description) {
    m_description = description;
}

void TheaterLights::on() {
    cout << *m_description << " on" << endl;
}

void TheaterLights::off() {
    cout << *m_description << " off" << endl;
}

void TheaterLights::dim(int level) {
    cout << *m_description << " dimming to " << level  << "%" << endl;
}

string TheaterLights::toString() {
    return *m_description;
}
