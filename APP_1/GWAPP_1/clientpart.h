#ifndef CLIENTPART_H
#define CLIENTPART_H

#include <QObject>
#include <QTcpSocket>
#include <QMessageBox>
class ClientPart : public QObject
{
    Q_OBJECT
public:
    explicit ClientPart(QObject *parent = nullptr);


    QTcpSocket* socket;
    QByteArray Data;

public slots:
    void sockReady();
    void sockDisc();

private slots:
    void on_pushButton_clicked();

};

#endif // CLIENTPART_H
