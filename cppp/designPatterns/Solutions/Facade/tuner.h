#ifndef TUNER_H
#define TUNER_H

#include <string>

class Amplifier;

class Tuner {
public:
    Tuner(std::string* description, Amplifier* amplifier);
    void on();
    void off();
    void setFrequency(double frequency);
    void setAm();
    void setFm();
    std::string toString();
private:
    std::string* m_description;
    Amplifier* m_amplifier;
    double m_frequency;
    
};

#endif //TUNER_H
