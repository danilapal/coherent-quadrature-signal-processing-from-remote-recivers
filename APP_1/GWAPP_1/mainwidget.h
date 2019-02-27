#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QMainWindow>
#include <controller.h>
#include <QGridLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QRadioButton>

namespace Ui {
class MainWidget;
}

class MainWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
   //  std::vector <COH_G35DDC_CALLBACKS> CallbacksV;
    ~MainWidget();

private:
    Ui::MainWidget *ui;
    std::shared_ptr<Controller> Controller;
    std::shared_ptr<QHBoxLayout>  grid;
    std::shared_ptr<QGroupBox>  men;
    void paintRadioView();
    QGroupBox *createGroup(INT32 Index);
};

#endif // MAINWIDGET_H
