#include <iostream>
#include <string>
#include "popcorn_popper.h"

using namespace std;

PopcornPopper::PopcornPopper(string* description) {
    m_description = description;
}

void PopcornPopper::on() {
    cout << *m_description << " on" << endl;
}

void PopcornPopper::off() {
    cout << *m_description << " off" << endl;
}

void PopcornPopper::pop() {
    cout << *m_description << " popping popcorn!" << endl;
}

string PopcornPopper::toString() {
    return *m_description;
}

