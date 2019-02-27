#include "client.h"
#include "radioview.h"
#include "radiotools.h"
#include <type_traits>
#include <QMutex>
namespace App{
static application * app =nullptr;
static QMutex mutex;
COH_G35DDC_GET_TIMESTAMP_COUNTERS CohGetTimestampCounters=(COH_G35DDC_GET_TIMESTAMP_COUNTERS)GetProcAddress(radioTools::hAPI,"CohGetTimestampCounters");
VOID __stdcall DDC1StreamCallback(UINT32 DeviceCount,CONST VOID **Buffers,UINT32 NumberOfSamples,UINT32 BitsPerSample,DWORD_PTR UserData) {
    mutex.lock();
     static bool t =false ;
        if (!t) {
            qDebug()<<DeviceCount<<"Num samples"<<NumberOfSamples<<"Bitpersample"<<BitsPerSample<<"UD"<<UserData;
            qDebug()<<"BEFORE";
             const INT32 *Nub = static_cast<const INT32*>(*(Buffers));
            for (UINT32 w=0;w<NumberOfSamples*2;w++) {
                qDebug()<<*(Nub+w);

            }
        }
        t=true;
    if (BitsPerSample==32) {
        std::vector<std::vector<INT32>> dataVector((unsigned int) DeviceCount);
        //std::vector<std::vector<INT32>> dataVectorI((unsigned int) DeviceCount);
       // std::vector<std::vector<INT32>> dataVectorQ((unsigned int) DeviceCount);
        for (UINT32 i=0 ; i<DeviceCount; i++) {

            const INT32 *intBuffers = static_cast<const INT32*>(*(Buffers+i));

            for (UINT32 q=0 ; q<NumberOfSamples*2;q++) {
                dataVector[i].push_back(*(intBuffers+q));
//                if ((q%2) ==1){
//                    dataVectorQ[i].push_back(*(intBuffers+q));
//                } else {
//                   dataVectorI[i].push_back(*(intBuffers+q));
//                }
            }

        }
        //app->getViewer()->PlotSample(1,dataVectorI,dataVectorQ,DeviceCount,NumberOfSamples);

        app->getViewer()->sendData(dataVector,UserData,DeviceCount,NumberOfSamples);
        mutex.unlock();
        //dataVector.clear();
        // qDebug()<<dataVector.size();
        //        if (!t) {
        //            qDebug()<<"AFTER";
        //            for (UINT32 w=0;w<dataVector[0].size();w++) {
        //                qDebug()<<dataVector[0][w];
        //            }
        //        }

    }

}

void start(application &widget)
{
    app = &widget;
    COH_G35DDC_CALLBACKS Callbacks;
    Callbacks.IFCallback =nullptr;
    Callbacks.DDC1StreamCallback =  DDC1StreamCallback;
    Callbacks.DDC2PreprocessedStreamCallback = nullptr;
    Callbacks.DDC2StreamCallback = nullptr;
    app->getViewer()->getController()->setControllerCallbaks(Callbacks,0);
    //radioTools::CohSetCallbacks(app->getViewer()->getController()->radioSetList[0]._DeviceSet,&Callbacks,1);
    //app->getViewer()->getController()->setControllerCallbaks()
    app->getViewer()->show();
    app->getViewer()->getController()->startDDC1();

}

//WINBOOL CohGetTimestampCounters(INT32 hDeviceSet, double *DDC1SampleCounter, UINT64 *ADCPeriodCounter)
//{
//    static bool t =false ;
//    if (!t)
//        qDebug()<<hDeviceSet<<"WORK TimeStamp";
//    t=true;
//    return true;
//}

}

//RadioViewer w ;
// w.show();


