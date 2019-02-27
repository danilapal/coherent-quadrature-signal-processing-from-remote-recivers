#ifndef RADIO_H
#define RADIO_H
#include "radiotools.h"
#include <iostream>
#include <memory>
class Radio
{
public:
    Radio();
    Radio(INT32 Device, UINT32 DeviceIndex, UINT32 DeviceNumber=1);
    INT32  _DeviceSet;
    UINT32 _DeviceIndex;
    UINT32 _DeviceNumber;

    //G35DDC_DEVICE_INFO  _info;
   // G35DDC_GET_DDC_INFO _DDCinfo;
private:


};

#endif // RADIO_H
