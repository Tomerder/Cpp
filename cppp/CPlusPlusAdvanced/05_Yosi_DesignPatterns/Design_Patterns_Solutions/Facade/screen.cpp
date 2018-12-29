#include <iostream>
#include <string>
#include "screen.h"

using namespace std;

Screen::Screen(string* description) {
    m_description = description;
}
 
void Screen::up() {
    cout << *m_description << " going up" << endl;
}
 
void Screen::down() {
    cout << *m_description << " going down" << endl;
}

string Screen::toString() {
    return *m_description;
}

