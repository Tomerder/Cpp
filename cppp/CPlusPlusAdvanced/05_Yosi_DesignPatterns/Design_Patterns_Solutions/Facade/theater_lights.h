#ifndef THEATER_LIGHTS_H
#define THEATER_LIGHTS_H

class TheaterLights {
public:    
    TheaterLights(std::string* description);
    void on();
    void off();
    void dim(int level);
    std::string toString();
private:
    std::string* m_description;
};

#endif //THEATER_LIGHTS_H
