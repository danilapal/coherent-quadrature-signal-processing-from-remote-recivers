
#ifndef CLIENT_H
#define CLIENT_H
#include "application.h"
namespace App{

void start(application &widget);
VOID __stdcall DDC1StreamCallback(UINT32 DeviceCount,CONST VOID **Buffers,UINT32 NumberOfSamples,UINT32 BitsPerSample,DWORD_PTR UserData);

extern COH_G35DDC_GET_TIMESTAMP_COUNTERS CohGetTimestampCounters;
}
#endif // CLIENT_H
