#include "radioviewer.h"
#include "ui_radioviewer.h"
#include <QRadioButton>
#include <QPushButton>
#include <QTimer>
RadioViewer::RadioViewer(QWidget *parent) :
    QWidget(parent),

    ui(new Ui::RadioViewer),
    controller(new class Controller),
    men(createGroup(createPlot())),
    men2(createGroup(plot2))
{
    this->plots.push_back(createPlot());

    this->box.push_back(createGroup(plots[0],1));
    //connect(this,SIGNAL(sendSamplesToPlot(UINT32)),this,SLOT(getSampleToPlot( UINT32)));
    ui->setupUi(this);
    this->ui->RadioData->setStretchFactor(men->layout(),100);

    this->ui->RadioData->addWidget(box[0]);
    //this->ui->RadioData->setStretchFactor(men->layout(),100);
    this->ui->scrollArea->resize(this->ui->scrollArea->width()+200,this->ui->scrollArea->height()+200);
    this->resize(this->width()+100,this->height()+100);
    //test graph
    ui->PIW->addGraph();
    ui->PIW->addGraph();;
    ui->PIW->graph(0)->setPen(QPen(QColor(255, 0, 0)));
    ui->PIW->graph(1)->setPen(QPen(QColor(0, 255, 0)));
    ui->PIW->graph(0)->setName("I");
    ui->PIW->graph(1)->setName("Q");
    ui->PIW->graph(0)->addToLegend();
    ui->PIW->graph(1)->addToLegend();
    ui->PIW->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    //connect();

    //test graph end


}

Controller *RadioViewer::getController()
{
    return this->controller.get();
}

RadioViewer::~RadioViewer()
{
    delete ui;
}

QCustomPlot *RadioViewer::createPlot()
{
    QCustomPlot *PlotWidget = new QCustomPlot();
    PlotWidget->addGraph();
    PlotWidget->graph(0)->setPen(QPen(QColor(255, 0, 0)));
    PlotWidget->addGraph();
    PlotWidget->graph(1)->setPen(QPen(QColor(0, 255, 0)));
    PlotWidget->graph(0)->setName("I");
    PlotWidget->graph(1)->setName("Q");
    PlotWidget->graph(0)->addToLegend();
    PlotWidget->graph(1)->addToLegend();
    PlotWidget->legend->setVisible(true);
    PlotWidget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    // ui->PlotWidget->xAxis->setTicker(timeTicker);
    PlotWidget->axisRect()->setupFullAxesBox();
    PlotWidget->xAxis->setLabel("time");
    PlotWidget->yAxis->setLabel("S(t)");
    PlotWidget->xAxis->setRange(0,2080);
    PlotWidget->yAxis->setRange(-100000,100000);
    connect( PlotWidget->xAxis, SIGNAL(rangeChanged(QCPRange)),  PlotWidget->xAxis2, SLOT(setRange(QCPRange)));
    connect( PlotWidget->yAxis, SIGNAL(rangeChanged(QCPRange)),  PlotWidget->yAxis2, SLOT(setRange(QCPRange)));
    PlotWidget->resize(PlotWidget->width()+500,PlotWidget->height()+300);

    return  PlotWidget;

}

//void RadioViewer::paintRadioView()
//{

//}

QGroupBox *RadioViewer::createGroup(QCustomPlot *plot, unsigned int index)
{
    QGroupBox *groupBox = new QGroupBox(tr("RadioData"));

    QRadioButton *radio1 = new QRadioButton(tr("&Radio button 1"));

    QPushButton *checkButton = new QPushButton(tr("& Check"));
    QPushButton *StartDDC1 =new QPushButton(tr("& StartDDC1"));
    connect(checkButton,&QPushButton::clicked,this,[this,index](){checkData(index);});
    radio1->setChecked(true);
    //QCustomPlot *plot = new QCustomPlot();
    //plot->addGraph();
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->stretch(1000);
    vbox->addWidget(radio1);
    vbox->addWidget(checkButton);
    vbox->addWidget(StartDDC1);
    vbox->addSpacing(5);
    vbox->addWidget(plot);


    //vbox->addStretch(1);

    groupBox->setLayout(vbox);
    groupBox->resize(groupBox->width()+500,groupBox->height()+550);
    return groupBox;
}

void RadioViewer::sendData(std::vector<std::vector<INT32> > data, UINT32 index,UINT32 deviceCounter,UINT32 NumberOfSamples)
{
    // qDebug()<<"START Sharing";
    PlotSample(index,data,deviceCounter,NumberOfSamples);
}

void RadioViewer::getSampleToPlot(UINT32 DeviceHandler)
{
    qDebug()<<"HEYHEYHET"<<DeviceHandler;
}

void RadioViewer::PlotSample(unsigned int plotIndex,std::vector<std::vector<INT32> > data,UINT32 deviceCounter,UINT32 NumberOfSamples)
{
    this->plots[plotIndex-1]->graph(0)->data().clear();
    this->plots[plotIndex-1]->graph(1)->data().clear();

    qDebug()<<"GIVE";
    //this->plots[plotIndex-1]->update();
    //qDebug()<<"DeviceCounter "<<deviceCounter<<"PL"<<plotIndex;
    for (UINT32 i=0 ;i<deviceCounter;i++) {

        for (UINT32 q=0;q<NumberOfSamples;q++) {

            this->plots[plotIndex-1]->graph(0)->addData(q,data[i][q*2]);
            this->plots[plotIndex-1]->graph(1)->addData(q,data[i][q*2+1]);
            // this->plots[plotIndex-1]->graph(0)->addData(q,dataI[i][q]);
            // this->plots[plotIndex-1]->graph(1)->addData(q,dataQ[i][q]);

        }


    }
    //this->plots[plotIndex-1]->replot();
    //this->plots[plotIndex-1]->update();


}

void RadioViewer::checkData(unsigned int index)
{
    qDebug()<<index;
    qDebug()<<this->getController()->radioSetList[index]._DeviceSet;


}
