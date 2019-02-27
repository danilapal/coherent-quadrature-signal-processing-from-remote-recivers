#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "radio.h"
#include <vector>
class Controller:public ICohG35DDCDeviceSetCallback
{

public:
    Controller();
    Controller(std::shared_ptr<ICohG35DDCDeviceSet> &DeviceSet,std::shared_ptr<G35DDC_DEVICE_INFO> &DevInfo);
    ~Controller(void);
    void power(bool power);
    void startDeviceDDC1(int bitw=2048);
    void stopDeviceDDC1();
    void setFrenq(int freq);
    void setBitw(int btw);
    BOOL getPowerState();
    void __stdcall CohG35DDC_DDC1StreamCallback(ICohG35DDCDeviceSet *DeviceSet,UINT32 DeviceCount,CONST VOID **Buffers,UINT32 NumberOfSamples,UINT32 BitsPerSample);
    void __stdcall CohG35DDC_IFCallback(ICohG35DDCDeviceSet *DeviceSet,UINT32 DeviceIndex,CONST SHORT *Buffer,UINT32 NumberOfSamples,WORD MaxADCAmplitude,UINT32 ADCSamplingRate);
    void __stdcall CohG35DDC_DDC2StreamCallback(ICohG35DDCDeviceSet *DeviceSet,UINT32 DeviceIndex,CONST FLOAT *Buffer,UINT32 NumberOfSamples);
    void __stdcall CohG35DDC_DDC2PreprocessedStreamCallback(ICohG35DDCDeviceSet *Device,UINT32 DeviceIndex,CONST FLOAT *Buffer,UINT32 NumberOfSamples,FLOAT SlevelPeak,FLOAT SlevelRMS);
    void __stdcall CohG35DDC_AudioStreamCallback(ICohG35DDCDeviceSet *Device,UINT32 DeviceIndex,UINT32 Type,CONST FLOAT *Buffer,UINT32 NumberOfSamples);


private:
    std::shared_ptr<ICohG35DDCDeviceSet> DeviceSet;
    std::shared_ptr<G35DDC_DEVICE_INFO> DevInfo;
    void DDC1StreamCallback(CONST VOID *Buffer,UINT32 NumberOfSamples,UINT32 BitsPerSample);
};

#endif // CONTROLLER_H
