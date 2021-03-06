#ifndef RADIOTOOLS_H
#define RADIOTOOLS_H
#include "G35DDCAPI.h"
#include "QDebug"
struct Packet
{
    Packet() {}
    std::vector<INT32> data;
};
namespace radioTools {
//API
extern HMODULE hAPI;


//common
//extern COH_G35DDC_GET_DEVICE_SET_LIST CohGetDeviceSetList;
//extern COH_G35DDC_FREE_DEVICE_SET_LIST CohFreeDeviceSetList;
//extern COH_G35DDC_OPEN_DEVICE_SET CohOpenDeviceSet;
//extern COH_G35DDC_CLOSE_DEVICE_SET CohCloseDeviceSet;
//extern COH_G35DDC_IS_CONNECTED CohIsConnected;
//extern COH_G35DDC_GET_DEVICE_COUNT CohGetDeviceCount;
//extern COH_G35DDC_GET_DEVICE_INFO CohGetDeviceInfo;
//extern COH_G35DDC_GET_DEVICE_INFOS CohGetDeviceInfos;
//extern COH_G35DDC_SET_POWER CohSetPower;
//extern COH_G35DDC_GET_POWER CohGetPower;
//// DDC1
//extern COH_G35DDC_GET_DDC_INFO CohGetDDCInfo;
//extern COH_G35DDC_GET_DDC1_COUNT CohGetDDC1Count;
//extern COH_G35DDC_SET_DDC1 CohSetDDC1;
//extern COH_G35DDC_GET_DDC1 CohGetDDC1;
//extern COH_G35DDC_SET_DDC1_FREQUENCY CohSetDDC1Frequency;
//extern COH_G35DDC_GET_DDC1_FREQUENCY CohGetDDC1Frequency;
//extern COH_G35DDC_SET_DDC1_PHASE_SHIFT CohSetDDC1PhaseShift;
//extern COH_G35DDC_GET_DDC1_PHASE_SHIFT CohGetDDC1PhaseShift;
//extern COH_G35DDC_START_DDC1 CohStartDDC1;
//extern COH_G35DDC_STOP_DDC1 CohStopDDC1;
////callbacks
//extern COH_G35DDC_SET_CALLBACKS CohSetCallbacks;


}
#endif // RADIOTOOLS_H
