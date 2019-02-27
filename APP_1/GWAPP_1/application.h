#ifndef APPLICATION_H
#define APPLICATION_H

#include "mainwidget.h"
#include "radioviewer.h"
class application
{
public:
    application();
    void start();
    RadioViewer *getViewer();
private:
    std::shared_ptr<RadioViewer> Viewer;
};
#endif // APPLICATION_H
