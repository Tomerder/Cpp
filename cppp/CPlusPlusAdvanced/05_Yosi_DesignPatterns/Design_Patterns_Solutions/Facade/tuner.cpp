#include <iostream>
#include <string>
#include "tuner.h"

using namespace std;

Tuner::Tuner(string* description, Amplifier* amplifier) {
    m_description = description;
}
 
void Tuner::on() {
    cout << *m_description << " on" << endl;
}
 
void Tuner::off() {
    cout << *m_description << " off" << endl;
}
 
void Tuner::setFrequency(double frequency) {
    cout << *m_description << " setting frequency to " << frequency << endl;
    m_frequency = frequency;
}
 
void Tuner::setAm() {
    cout << *m_description << " setting AM mode" << endl;
}
 
void Tuner::setFm() {
    cout << *m_description << " setting FM mode" << endl;
}
  
string Tuner::toString() {
    return *m_description;
}

