#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <controller.h>
#include <QTcpSocket>
#include <QMutex>
#include <QWaitCondition>
#include <QReadLocker>
#include <QWriteLocker>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();


    Controller *getController();
private slots:


    void on_startDDCButton_clicked();
    void on_powerButton_clicked();
    void on_stopDDCButtton_clicked();
    void on_FreqSiftCenter_editingFinished();
    void on_Bitper_editingFinished();
    void on_checkbotton_clicked();
    void sockReady();
    void sockDisc();

    void on_serverTest_clicked();

private:
    G3XDDCAPI_CREATE_INSTANCE CreateInstance;
    std::shared_ptr<ICohG35DDCDeviceSetEnumerator> Enumerator;
    std::shared_ptr<Controller> controller;
    Ui::Widget *ui;
    QTcpSocket* socket;
    QByteArray Data;
    G3XDDCAPI_CREATE_INSTANCE createInstance();
    QMutex Mutex;
    QReadWriteLock mutex;
    QWaitCondition notEmpty;
    void setupPlot();
public slots:
    void testslot() ;
signals:
    void testsignal();

};

#endif // WIDGET_H
