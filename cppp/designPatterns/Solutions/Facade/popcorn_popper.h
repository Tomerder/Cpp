#ifndef POPCORN_POPPER
#define POPCORN_POPPER

#include <string>

class PopcornPopper {
public:
    PopcornPopper(std::string* description);
    void on();
    void off();
    void pop();
    std::string toString();
private:
    std::string* m_description;
};

#endif //POPCORN_POPPER
