#include "application.h"
#include <QApplication>
#include "radioviewer.h"
#include "client.h"
VOID __stdcall DDC1StreamCallback(UINT32 DeviceCount,CONST VOID **Buffers,UINT32 NumberOfSamples,UINT32 BitsPerSample,DWORD_PTR UserData);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    application app;
    App::start(app);
    return a.exec();
}

