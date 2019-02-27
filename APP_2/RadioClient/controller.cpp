#include "controller.h"
#include <QtDebug>
Controller::Controller():
    DeviceSet(nullptr),
    DevInfo(nullptr)

{


}

Controller::Controller(std::shared_ptr<ICohG35DDCDeviceSet> &DeviceSet, std::shared_ptr<G35DDC_DEVICE_INFO> &DevInfo):
    DeviceSet(DeviceSet),
    DevInfo(DevInfo)
{
    if(this->DeviceSet->Open(DevInfo.get(),1))
        qDebug()<<"DeviceSet opened";
    this->DeviceSet->SetCallback(this);
}

Controller::~Controller()
{
    this->DeviceSet->SetPower(false);
    this->DeviceSet->Close();
    this->DeviceSet->Release();
}

void Controller::power(bool power)
{
    this->DeviceSet->SetPower((BOOL)power);
}

void Controller::startDeviceDDC1(int bitw)
{
    this->DeviceSet->StartDDC1(2048);
}

void Controller::stopDeviceDDC1()
{
    this->DeviceSet->StopDDC1();
}

void Controller::setFrenq(int freq)
{
    this->DeviceSet->SetDDC1Frequency((UINT32)freq);
}

void Controller::setBitw(int btw)
{


}

WINBOOL Controller::getPowerState()
{
    BOOL power;
    this->DeviceSet->GetPower(&power);
    return power;
}


void Controller::CohG35DDC_DDC1StreamCallback(ICohG35DDCDeviceSet *DeviceSet, UINT32 DeviceCount, const void **Buffers, UINT32 NumberOfSamples, UINT32 BitsPerSample)
{
    qDebug()<<"DDC1Steram";
    for (uint32_t i=0;i<DeviceCount;i++) {
        DDC1StreamCallback(Buffers[i],NumberOfSamples, BitsPerSample);
    }

}

void Controller::CohG35DDC_IFCallback(ICohG35DDCDeviceSet *DeviceSet, UINT32 DeviceIndex, const SHORT *Buffer, UINT32 NumberOfSamples, WORD MaxADCAmplitude, UINT32 ADCSamplingRate)
{
    Q_UNUSED(DeviceSet);
    Q_UNUSED(DeviceIndex);
    Q_UNUSED(Buffer);
    Q_UNUSED(NumberOfSamples);
    Q_UNUSED(MaxADCAmplitude);
}

void Controller::CohG35DDC_DDC2StreamCallback(ICohG35DDCDeviceSet *DeviceSet, UINT32 DeviceIndex, const FLOAT *Buffer, UINT32 NumberOfSamples)
{
    Q_UNUSED(DeviceSet);
    Q_UNUSED(DeviceIndex);
    Q_UNUSED(Buffer);
    Q_UNUSED(NumberOfSamples);
}

void Controller::CohG35DDC_DDC2PreprocessedStreamCallback(ICohG35DDCDeviceSet *Device, UINT32 DeviceIndex, const FLOAT *Buffer, UINT32 NumberOfSamples, FLOAT SlevelPeak, FLOAT SlevelRMS)
{
    Q_UNUSED(Device);
    Q_UNUSED(DeviceIndex);
    Q_UNUSED(Buffer);
    Q_UNUSED(NumberOfSamples);
    Q_UNUSED(SlevelPeak);
    Q_UNUSED( SlevelRMS);
}

void Controller::CohG35DDC_AudioStreamCallback(ICohG35DDCDeviceSet *Device, UINT32 DeviceIndex, UINT32 Type, const FLOAT *Buffer, UINT32 NumberOfSamples)
{
    Q_UNUSED(Device);
    Q_UNUSED(DeviceIndex);
    Q_UNUSED(Buffer);
    Q_UNUSED(NumberOfSamples);
    Q_UNUSED(Type);
}

void Controller::DDC1StreamCallback(const void *Buffer, UINT32 NumberOfSamples, UINT32 BitsPerSample)
{

}
