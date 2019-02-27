#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "radio.h"
#include <vector>
class Controller
{

public:
    Controller();
    Controller(std::vector<Radio> radioSetList);
    ~Controller();
    bool setCallbaks ();
    INT32 openDevice(UINT32 DeviceSet, UINT32 counter);
    void openDemo(UINT32 Devicesize);
    void turnUp();
    void turnUp(INT32 DeviceSet);
    void turnDown();
    void turnDown(INT32 DeviceSet);
    void startDDC1();
    void startDDC1(INT32 DeviceSet);
    void stopDDC1();
    void stopDDC1(INT32 DeviceSet);
    void setDDC1 ();
    void setDDC1(INT32 DeviceSet);
    void setControllerCallbaks(COH_G35DDC_CALLBACKS &Callbacks,unsigned int deviceSet );

    std::vector<COH_G35DDC_CALLBACKS> CallbaksVector;
    std::vector<Radio> radioSetList;

private:

    COH_G35DDC_DEVICE_SET_LIST *DeviceSetList;



};

#endif // CONTROLLER_H
