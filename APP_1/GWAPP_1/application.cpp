#include "application.h"

application::application():
Viewer(new RadioViewer())
{

}

void application::start()
{
    this->Viewer->show();
}

RadioViewer *application::getViewer()
{
    return this->Viewer.get();
}
