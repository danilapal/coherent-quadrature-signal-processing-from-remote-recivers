#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QInputDialog>
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
                printf("Available G35DDC device set count=%d:\n",SetCount);
                for (size_t i;i<=SetCount;i++) {
                    items <<QString(QString::number(i));
                }

            }
            else
            {
                printf("No available G35DDC device set found.\n");
            }


        }
        else
        {
            printf("Failed to create enumerator object. \n",GetLastError());
        }


    }
    else
    {
        printf("Failed to load G35DDCAPI.dll.\n");
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
    if (radioIndex>=0) {

        UINT32 Count=0;
        Enumerator->GetDeviceSetInfo((UINT32)radioIndex,nullptr,&Count);
        // G35DDC_DEVICE_INFO *DevInfo;
        //ICohG35DDCDeviceSet *DeviceSet;
        std::shared_ptr<ICohG35DDCDeviceSet> DeviceSet;
        std::shared_ptr<G35DDC_DEVICE_INFO> DevInfo(new G35DDC_DEVICE_INFO[Count]);
        Enumerator->GetDeviceSetInfo(0,DevInfo.get(),&Count);

        CreateInstance(G35DDC_CLASS_ID_COH_DEVICE_SET,(void**)&DeviceSet);
        this->controller.reset(new Controller(DeviceSet,DevInfo));
    }

    socket = new QTcpSocket(this);
        connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
        connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));

    ui->setupUi(this);
}



Widget::~Widget()
{
    this->controller->Controller::~Controller();
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



void Widget::on_startDDCButton_clicked()
{
    this->getController()->startDeviceDDC1(ui->Bitper->text().toInt());
}

void Widget::on_powerButton_clicked()
{
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
