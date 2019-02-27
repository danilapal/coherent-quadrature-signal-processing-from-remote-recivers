#include "controller.h"
#include <QtDebug>
Controller::Controller()//:
//DeviceSetList(new COH_G35DDC_DEVICE_SET_LIST(*radioTools::CohGetDeviceSetList()))
{
    //setList
    this->DeviceSetList =radioTools::CohGetDeviceSetList();
    bool demo =true ;
    if(radioTools::hAPI!=nullptr) {
        if (!demo) {
            if(DeviceSetList!=nullptr) {
                if(DeviceSetList->DeviceSetCount!=0)
                {
                    qDebug()<<"Available G35DDC device set count="<<DeviceSetList->DeviceSetCount;
                    UINT32 counter=1;
                    for(UINT32 i=0;i<DeviceSetList->DeviceSetCount;i++)
                    {
                        INT32 hDeviceSet = openDevice(i,counter);
                        this->radioSetList.push_back(Radio(hDeviceSet,counter));
                        counter++;
                    }
                }
            } else qDebug()<<"No ava DeviceSets";

        }

        else {
            qDebug()<<"OPEN DEMO VERSION";
            openDemo(1);
        }


    }

}

Controller::Controller(std::vector<Radio> radioSetList):
    radioSetList(radioSetList)

{
   // this->radioSetList = radioSetList;
}

Controller::~Controller()
{   stopDDC1();
    for (UINT32 i = 0 ;i< this->radioSetList.size(); i++) {

        if (radioTools::CohCloseDeviceSet(this->radioSetList[i]._DeviceSet))
            qDebug()<<"DiveceList "<< i <<" closed";
    }
    radioTools::CohFreeDeviceSetList(this->DeviceSetList);
    FreeLibrary(radioTools::hAPI);
}

INT32 Controller::openDevice(UINT32 DeviceSet,UINT32 counter)
{

    INT32 hDeviceSet;
    //Opening the first available G35DDC device set using predefined G35DDC_OPEN_FIRST_SET constant
    hDeviceSet=radioTools::CohOpenDeviceSet(DeviceSetList->DeviceSet[DeviceSet].DeviceInfo,DeviceSetList->DeviceSet[DeviceSet].DeviceCount);

    if(hDeviceSet>=0) {
        //this->radioSetList.push_back(Radio(hDeviceSet,counter));
        // to do
        //put ifno
    }
    else {
        qDebug()<<"CohOpenDeviceSet failed with error %08X\n";
    }
    return hDeviceSet;
}

void Controller::openDemo(UINT32 Devicesize)
{

    INT32 hDeviceSet =radioTools::CohOpenDeviceSet(nullptr,Devicesize);
    qDebug()<<"HDeviceSet"<<hDeviceSet;
    if(hDeviceSet>=0) {

        this->radioSetList.push_back(Radio(hDeviceSet,1));

    }
    else {
        qDebug()<<"CohOpenDeviceSet failed with error %08X\n";
    }
}

void Controller::turnUp()
{
    for (UINT32 i =0 ; i< this->radioSetList.size() ; i++)
        turnUp(this->radioSetList[i]._DeviceSet);
}

void Controller::turnUp(INT32 DeviceSet)
{
    if(!radioTools::CohSetPower(DeviceSet, true))
        qDebug()<<"Device "<<DeviceSet<<" Not powered";
}

void Controller::turnDown()
{
    for (UINT32 i =0 ; i< this->radioSetList.size() ; i++)
        turnDown(this->radioSetList[i]._DeviceSet);
}

void Controller::turnDown(INT32 DeviceSet)
{
    radioTools::CohSetPower(DeviceSet, false );
}

void Controller::startDDC1()
{

    for (UINT32 i =0 ; i< this->radioSetList.size() ; i++){
        turnUp(this->radioSetList[i]._DeviceSet);
        startDDC1(this->radioSetList[i]._DeviceSet);
    }
}

void Controller::startDDC1(INT32 DeviceSet)
{
    if(!radioTools::CohStartDDC1(DeviceSet,1))
        qDebug()<<"DDC1 for "<<DeviceSet<<" not started";//1
}

void Controller::stopDDC1()
{
    for (UINT32 i =0 ; i< this->radioSetList.size() ; i++)
        stopDDC1(this->radioSetList[i]._DeviceSet);
}

void Controller::stopDDC1(INT32 DeviceSet)
{
    radioTools::CohStopDDC1(DeviceSet);
}

void Controller::setDDC1()
{
    for (UINT32 i =0 ; i< this->radioSetList.size() ; i++)
        setDDC1(this->radioSetList[i]._DeviceSet);
}

void Controller::setDDC1(INT32 DeviceSet)
{

}

void Controller::setControllerCallbaks(COH_G35DDC_CALLBACKS &Callbacks, unsigned int deviceSet)
{


    radioTools::CohSetCallbacks(radioSetList[deviceSet]._DeviceSet,&Callbacks,this->radioSetList[deviceSet]._DeviceIndex);
}
