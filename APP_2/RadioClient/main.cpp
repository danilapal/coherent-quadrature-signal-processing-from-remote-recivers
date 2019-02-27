#include "widget.h"
#include <QApplication>
#include <QMessageBox>
#include <radiotools.h>
#include <QComboBox>
#include <QInputDialog>
#include <QDebug>
#include <radiotools.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   Widget w;

    w.show();

    return a.exec();
}
