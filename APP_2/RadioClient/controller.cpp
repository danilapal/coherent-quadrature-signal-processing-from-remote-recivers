#include "controller.h"
#include <QtDebug>

Controller::Controller():
    DeviceSet(nullptr),
    DevInfo(nullptr)

{


}

Controller::Controller(std::shared_ptr<ICohG35DDCDeviceSet> &DeviceSet, std::shared_ptr<G35DDC_DEVICE_INFO> &DevInfo, bool demo, UINT32 Count, int bufferSize):
    DeviceSet(DeviceSet),
    DevInfo(DevInfo),
    DDC1Buffer(new RingBuffer((quint32)bufferSize))
{
    if (!demo) {
        if(this->DeviceSet->Open(DevInfo.get(),Count))
            qDebug()<<"DeviceSet opened";
    }
    else {
        qDebug()<<"Demo opened";
        DeviceSet->Open(nullptr,1); //G35DDC_OPEN_DEMO_SET
    }
    this->DeviceSet->SetCallback(this);
    timer = std::shared_ptr<QTimer>(new QTimer());
    //connect(timer.get(), &QTimer::timeout,)
    //this->plot.reset(Nplot);
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
    this->DeviceSet->StartDDC1((UINT32)bitw);
}

void Controller::stopDeviceDDC1()
{
    this->DeviceSet->StopDDC1();
    DDC1Buffer->clean();
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

void Controller::fillFileData(DDC1StreamCallbackData &DDC1data, double DDC1Count, UINT64 ADCCount)
{
    // to do make packet
    for (uint32_t i=0;i<DDC1data.DeviceCount;i++) {
        DDC1StreamCallback(DDC1data.Buffers[i],DDC1data.NumberOfSamples, DDC1data.BitsPerSample);
    }
    //
}

std::shared_ptr<ICohG35DDCDeviceSet> Controller::getDevice()
{
    return this->DeviceSet;
}


void Controller::CohG35DDC_DDC1StreamCallback(ICohG35DDCDeviceSet *DeviceSet, UINT32 DeviceCount, const void **Buffers, UINT32 NumberOfSamples, UINT32 BitsPerSample)
{

    qDebug()<<"DDC1CALLBACK";
    double DDC1Count = 0;
    UINT64 ADCCount = 0;
    DeviceSet-> GetTimestampCounters(&DDC1Count,&ADCCount);
    DDC1StreamCallbackData DDC1data;
    DDC1data.BitsPerSample=BitsPerSample;
    DDC1data.Buffers=Buffers;
    DDC1data.DeviceCount=DeviceCount;
    DDC1data.DeviceSet=DeviceSet;
    DDC1data.NumberOfSamples=NumberOfSamples;
    this->fillFileData(DDC1data,DDC1Count,ADCCount);

    if (BitsPerSample==32) {
        qDebug()<<"data Size"<<data32.size();
        this->data32.clear();
    }
    else {
        qDebug()<<"data Size"<<data16.size();
        this->data16.clear();
    }

    qDebug()<<"Buffer out"<<data32.size();

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
    Q_UNUSED(SlevelRMS);
}

void Controller::CohG35DDC_AudioStreamCallback(ICohG35DDCDeviceSet *Device, UINT32 DeviceIndex, UINT32 Type, const FLOAT *Buffer, UINT32 NumberOfSamples)
{
    Q_UNUSED(Device);
    Q_UNUSED(DeviceIndex);
    Q_UNUSED(Buffer);
    Q_UNUSED(NumberOfSamples);
    Q_UNUSED(Type);
}

std::vector<INT32> Controller::getData32()
{
    return this->data32;
}

RingBuffer *Controller::getDDC1Buffer()
{
    return this->DDC1Buffer.get();

}

void Controller::testslot()
{
    qDebug()<<"Timer";
}

void Controller::DDC1StreamCallback(const void *Buffer, UINT32 NumberOfSamples, UINT32 BitsPerSample)
{
    // to do template
    qDebug()<<"DDC1DATAGET";
    Packet DData32;
    if (BitsPerSample==32) {
        for (UINT32 i =0 ;i<NumberOfSamples*2;i++) {
            const INT32 *intBuffer = static_cast<const INT32*> (Buffer);
            INT32 sample =  *(intBuffer+i);
            //this->data32.push_back(sample);
            DData32.data.push_back(sample);
        }
    }
    else {
        for (UINT16 i =0 ;i<NumberOfSamples*2;i++) {
            const INT16 *intBuffer = static_cast<const INT16*> (Buffer);
            INT16 sample =  *(intBuffer+i);
            this->data16.push_back(sample);

        }
    }
    //Mutex.lock();
    qDebug()<<"Push";
    DDC1Buffer->push(DData32);
    qDebug()<<"PushENd";
    emit(this->testsignal());
    //Mutex.unlock();
}
