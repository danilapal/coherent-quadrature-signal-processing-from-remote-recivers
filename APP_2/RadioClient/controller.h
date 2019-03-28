#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "radio.h"
#include <vector>
#include <QObject>
#include <QMutex>
#include <QTimer>
#include <QWaitCondition>
#include <QReadLocker>
#include <QWriteLocker>
#include <qcustomplot.h>
#include <ringbuffer.h>
struct DDC1StreamCallbackData {
    ICohG35DDCDeviceSet *DeviceSet;
    unsigned int DeviceCount;
    const void **Buffers;
    unsigned int NumberOfSamples;
    unsigned int BitsPerSample;
    // double DDC1Count;
    // UINT64 ADCCount;
};
class Controller:public QObject,public ICohG35DDCDeviceSetCallback
{
    Q_OBJECT
public:
    Controller();
    Controller(std::shared_ptr<ICohG35DDCDeviceSet> &DeviceSet, std::shared_ptr<G35DDC_DEVICE_INFO> &DevInfo, bool demo =false , UINT32 Count =1,int bufferSize = 16);
    virtual ~Controller(void);
    void power(bool power);
    void startDeviceDDC1(int bitw=2048);
    void stopDeviceDDC1();
    void setFrenq(int freq);
    void setBitw(int btw);
    BOOL getPowerState();
    void fillFileData(DDC1StreamCallbackData &DDC1data,double DDC1Count,UINT64 ADCCount);
    std::shared_ptr<ICohG35DDCDeviceSet> getDevice();
    void __stdcall CohG35DDC_DDC1StreamCallback(ICohG35DDCDeviceSet *DeviceSet,UINT32 DeviceCount,CONST VOID **Buffers,UINT32 NumberOfSamples,UINT32 BitsPerSample);
    void __stdcall CohG35DDC_IFCallback(ICohG35DDCDeviceSet *DeviceSet,UINT32 DeviceIndex,CONST SHORT *Buffer,UINT32 NumberOfSamples,WORD MaxADCAmplitude,UINT32 ADCSamplingRate);
    void __stdcall CohG35DDC_DDC2StreamCallback(ICohG35DDCDeviceSet *DeviceSet,UINT32 DeviceIndex,CONST FLOAT *Buffer,UINT32 NumberOfSamples);
    void __stdcall CohG35DDC_DDC2PreprocessedStreamCallback(ICohG35DDCDeviceSet *Device,UINT32 DeviceIndex,CONST FLOAT *Buffer,UINT32 NumberOfSamples,FLOAT SlevelPeak,FLOAT SlevelRMS);
    void __stdcall CohG35DDC_AudioStreamCallback(ICohG35DDCDeviceSet *Device,UINT32 DeviceIndex,UINT32 Type,CONST FLOAT *Buffer,UINT32 NumberOfSamples);
    std::vector<INT32> getData32();
    RingBuffer *getDDC1Buffer();
signals:
    void testsignal();
public slots:
    void testslot() ;
private:
    std::shared_ptr<ICohG35DDCDeviceSet> DeviceSet;
    std::shared_ptr<G35DDC_DEVICE_INFO> DevInfo;
    QMutex Mutex;
    // to do - template data class
    //
    std::vector<INT32> data32;
    std::vector<INT16> data16;
    //
    void DDC1StreamCallback(CONST VOID *Buffer,UINT32 NumberOfSamples,UINT32 BitsPerSample);
    std::shared_ptr<QTimer> timer;
    //QReadWriteLock mutex;
    //QWaitCondition notEmpty;
    std::shared_ptr<RingBuffer> DDC1Buffer;


};

#endif // CONTROLLER_H
