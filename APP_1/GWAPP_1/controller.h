#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "radio.h"
#include <vector>
class Controller
{
public:
    Controller();
    std::vector<Radio> radioSet;
private:
};

#endif // CONTROLLER_H
