#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>
#include <qcustomplot.h>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    CreateInstance(this->createInstance()),
    Enumerator(nullptr),
    controller(nullptr),
    ui(new Ui::Widget)
{
    QInputDialog qDialog ;
    QStringList items;
    UINT32 SetCount;
    if(radioTools::hAPI!=nullptr)
    {
        CreateInstance=(G3XDDCAPI_CREATE_INSTANCE)GetProcAddress(radioTools::hAPI,"CreateInstance");

        if(CreateInstance(G35DDC_CLASS_ID_COH_DEVICE_SET_ENUMERATOR,(void**)&Enumerator))
        {
            Enumerator->Enumerate();

            SetCount=Enumerator->GetDeviceSetCount();

            if(SetCount!=0)
            {
                qDebug()<<"DEV AVA"<<SetCount;
                for (size_t i=0;i<SetCount;i++) {
                    items <<QString(QString::number(i));
                }
            }
            else
            {
                qDebug()<<"No available G35DDC device set found";
            }
        }
        else
        {
            qDebug()<<"Failed to create enumerator object";
        }
    }
    else
    {
        qDebug()<<("Failed to load G35DDCAPI.dll");
        exit(1);
    }
    items <<QString("Demo");
    qDialog.setOptions(QInputDialog::UseListViewForComboBoxItems);
    qDialog.setComboBoxItems(items);
    qDialog.setWindowTitle("Choose Device set index");
    int radioIndex=-1;
    if(qDialog.exec()) {

        radioIndex=qDialog.comboBoxItems().indexOf(qDialog.textValue());
    }
    if ((radioIndex>=0)) {

        UINT32 Count=0;
        Enumerator->GetDeviceSetInfo((UINT32)radioIndex,nullptr,&Count);
        std::shared_ptr<ICohG35DDCDeviceSet> DeviceSet;
        std::shared_ptr<G35DDC_DEVICE_INFO> DevInfo(new G35DDC_DEVICE_INFO[Count]);
        Enumerator->GetDeviceSetInfo(radioIndex,DevInfo.get(),&Count);
        CreateInstance(G35DDC_CLASS_ID_COH_DEVICE_SET,(void**)&DeviceSet);
        if ((qDialog.textValue()!="Demo")) {

            this->controller.reset(new Controller(DeviceSet,DevInfo));
        }
        else {
            qDebug()<<"DEMO";

            this->controller.reset(new Controller(DeviceSet,DevInfo,true,1));
        }


    }

    //
    // socket
    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
    // plot
    ui->setupUi(this);
    this->setupPlot();

    //

    connect(this->controller.get(),&Controller::testsignal,this,&Widget::testslot);
    //connect(this,&Widget::testsignal,this->controller.get(),&Controller::testslot);
}



Widget::~Widget()
{
    this->Enumerator->Release();
    delete ui;
}

Controller *Widget::getController()
{
    return this->controller.get();
}



G3XDDCAPI_CREATE_INSTANCE Widget::createInstance()
{
    return (G3XDDCAPI_CREATE_INSTANCE)GetProcAddress(radioTools::hAPI,"CreateInstance");
}

void Widget::setupPlot()
{
    ui->PlotWidget->addGraph();
    ui->PlotWidget->graph(0)->setPen(QPen(QColor(255, 0, 0)));
    ui->PlotWidget->addGraph();
    ui->PlotWidget->graph(1)->setPen(QPen(QColor(0, 255, 0)));
    ui->PlotWidget->graph(0)->setName("I");
    ui->PlotWidget->graph(1)->setName("Q");
    ui->PlotWidget->graph(0)->addToLegend();
    ui->PlotWidget->graph(1)->addToLegend();
    ui->PlotWidget->legend->setVisible(true);
    ui->PlotWidget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->PlotWidget->axisRect()->setupFullAxesBox();
    ui->PlotWidget->xAxis->setLabel("time");
    ui->PlotWidget->yAxis->setLabel("S(t)");
    ui->PlotWidget->xAxis->setRange(0,2080);
    ui->PlotWidget->yAxis->setRange(-1000000,1000000);
    // make left and bottom axes transfer their ranges to right and top axes:
    connect( ui->PlotWidget->xAxis, SIGNAL(rangeChanged(QCPRange)),  ui->PlotWidget->xAxis2, SLOT(setRange(QCPRange)));
    connect( ui->PlotWidget->yAxis, SIGNAL(rangeChanged(QCPRange)),  ui->PlotWidget->yAxis2, SLOT(setRange(QCPRange)));
    //
}

void Widget::testslot()
{
    //this->Mutex.lock();
    //std::vector<INT32> data32=this->getController()->getData32();
    Packet data32;
    quint32 q=0;
    if (this->getController()->getDDC1Buffer()->pop(data32)) {
        qDebug()<<"Slot";
        qDebug()<<"Slot Size"<<data32.data.size();
        ui->PlotWidget->graph(0)->data()->clear();
        ui->PlotWidget->graph(1)->data()->clear();

        // if(data32.size()!=0) {
        for (UINT32 i =0;i<data32.data.size()/2;i++) {

            ui->PlotWidget->graph(0)->addData(i,data32.data[2*i]);
            ui->PlotWidget->graph(1)->addData(i,data32.data[2*i+1]);
        }
        //  }
        // this->Mutex.unlock();
        ui->PlotWidget->replot();
    } else {
        qDebug()<<"FALSE";
    }
}

void Widget::on_startDDCButton_clicked()
{
    qDebug()<<"DDC1Start";
    this->getController()->startDeviceDDC1(ui->Bitper->text().toInt());
}

void Widget::on_powerButton_clicked()
{  // emit(this->testsignal());
    BOOL power=this->getController()->getPowerState();
    if (power) {
        this->getController()->power(false);
        ui->powerButton->setText(tr("OFF"));

    }
    else {
        this->getController()->power(true);
        ui->powerButton->setText(tr("ON"));
    }
}

void Widget::on_stopDDCButtton_clicked()
{
    qDebug()<<"stopDDC1";
    this->getController()->stopDeviceDDC1();
}

void Widget::on_FreqSiftCenter_editingFinished()
{
    this->getController()->setFrenq(ui->FreqSiftCenter->text().toInt());
}

void Widget::on_Bitper_editingFinished()
{

}
void Widget::on_checkbotton_clicked()
{
    UINT32 freq;
    double PhaseShift;
    UINT32 Count;
    this->getController()->getDevice()->GetDDC1Frequency(&freq);
    this->getController()->getDevice()->GetDDC1Count(&Count);
    this->getController()->getDevice()->GetDDC1PhaseShift(0,&PhaseShift);
    qDebug()<<"COUNT"<<Count;
    qDebug()<<"Freq"<<freq;
    qDebug()<<"PhaseShift"<<PhaseShift;

}
void Widget::sockReady()
{

    if (socket->waitForConnected(500))
    {
        socket->waitForReadyRead(500);
        Data = socket->readAll();
        qDebug()<<Data;
    }
}

void Widget::sockDisc()
{

}

void Widget::on_serverTest_clicked()
{
    socket->connectToHost("127.0.0.1",5555);
}
