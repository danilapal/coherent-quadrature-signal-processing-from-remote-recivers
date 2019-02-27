#include "radio.h"

Radio::Radio():
    _DeviceSet(-1),
    _DeviceIndex(0),
    _DeviceNumber(0)

{

}

Radio::Radio(INT32 Device, UINT32 DeviceIndex, UINT32 DeviceNumber):
    _DeviceSet(Device),
    _DeviceIndex(DeviceIndex),
    _DeviceNumber(DeviceNumber)
{

}
