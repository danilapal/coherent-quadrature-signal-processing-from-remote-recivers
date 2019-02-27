#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWidget),
    Controller(new class Controller()),
    grid(new QHBoxLayout()),
    men(createGroup(1))
{
    //grid->addWidget(men.get());
   // ui->MainWidget::centralWidget->addWidget(men.get());
    ui->setupUi(this);

}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::paintRadioView()
{


}

QGroupBox *MainWidget::createGroup(INT32 Index)
{
    QGroupBox *groupBox = new QGroupBox(tr("RadioData"));
    QRadioButton *radio1 = new QRadioButton(tr("&Radio button 1"));
    QRadioButton *radio2 = new QRadioButton(tr("&Radio button 2"));
    QRadioButton *radio3 = new QRadioButton(tr("&Radio button 3"));

    radio1->setChecked(true);

    //plot->addGraph();
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);
    vbox->addWidget(radio3);

    vbox->addStretch(1);
    groupBox->setLayout(vbox);
    return groupBox;
}
