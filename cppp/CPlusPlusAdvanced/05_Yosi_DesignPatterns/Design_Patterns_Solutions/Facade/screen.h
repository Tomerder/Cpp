#ifndef SCREEN_H
#define SCREEN_H

#include <string>

class Screen {
public:
    Screen(std::string* description);
    void up();
    void down();
    std::string toString();
private:
    std::string* m_description;
};

#endif //SCREEN_H
