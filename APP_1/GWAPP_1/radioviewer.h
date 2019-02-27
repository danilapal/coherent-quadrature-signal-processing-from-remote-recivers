#ifndef RADIOVIEWER_H
#define RADIOVIEWER_H

#include <QWidget>
#include <memory>
#include <QGroupBox>
#include <QHBoxLayout>
#include "radiotools.h"
#include "controller.h"
#include "qcustomplot.h"
namespace Ui {
class RadioViewer;
}

class RadioViewer : public QWidget
{
    Q_OBJECT

public:
    explicit RadioViewer(QWidget *parent = nullptr);
    Controller *getController();
     std::vector<QCustomPlot*> plots;

    ~RadioViewer();

private:
    Ui::RadioViewer *ui;
    QCustomPlot *plot = new QCustomPlot();
    QCustomPlot *plot2 = new QCustomPlot();

    std::shared_ptr<Controller> controller;
    //std::shared_ptr<QHBoxLayout>  grid;
    std::shared_ptr<QGroupBox>  men;
    std::shared_ptr<QGroupBox> men2;
    //void paintRadioView();

    std::vector<QGroupBox*> box;
    QCustomPlot *createPlot();
    QGroupBox *createGroup(QCustomPlot *plot,unsigned int index=0);



public:
    void sendData(std::vector<std::vector<INT32>> data, UINT32 index, UINT32 deviceCounter,UINT32 NumberOfSamples);




signals:
    void sendSamplesToPlot(UINT32 DeviceHandler);

public slots:
    void getSampleToPlot(UINT32 DeviceHandler);
    void PlotSample(unsigned int plotIndex,std::vector<std::vector<INT32> > data,UINT32 deviceCounter,UINT32 NumberOfSamples);
     //void PlotSample(unsigned int plotIndex, std::vector<std::vector<INT32> > dataI, std::vector<std::vector<INT32> > dataQ, UINT32 deviceCounter, UINT32 NumberOfSamples);
    void checkData(unsigned int index);
};

#endif // RADIOVIEWER_H
