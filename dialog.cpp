#include "dialog.h"
#include "ui_dialog.h"
#include "timerthread.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(this->ui->c1Box,SIGNAL(currentIndexChanged(int)),this,SLOT(comValue()));
    connect(this->ui->c2Box,SIGNAL(currentIndexChanged(int)),this,SLOT(comValue()));
    connect(this->ui->c3Box,SIGNAL(currentIndexChanged(int)),this,SLOT(comValue()));
    connect(this->ui->c4Box,SIGNAL(currentIndexChanged(int)),this,SLOT(comValue()));
    connect(this->ui->c5Box,SIGNAL(currentIndexChanged(int)),this,SLOT(comValue()));
    connect(this->ui->c6Box,SIGNAL(currentIndexChanged(int)),this,SLOT(comValue()));
    connect(this->ui->c7Box,SIGNAL(currentIndexChanged(int)),this,SLOT(comValue()));
    connect(this->ui->c8Box,SIGNAL(currentIndexChanged(int)),this,SLOT(comValue()));

    //connect(this->ui->hdial,SIGNAL(valueChanged(int)),this,SLOT(setHValue(int)));
    //connect(this->ui->ldial,SIGNAL(valueChanged(int)),this,SLOT(setLValue(int)));
    connect(&mTimerThread,SIGNAL(gpioHL(int)),this,SLOT(setHLStatus(int)));
    connect(&mTimerThread,SIGNAL(oneWorkStop(int)),this,SLOT(setSumValue(int)));

    this->ui->label->setText("STATUS: Stop");
    this->ui->c1Box->setCurrentIndex(10);
    this->ui->c2Box->setCurrentIndex(9);
    this->ui->c3Box->setCurrentIndex(5);
    this->ui->c4Box->setCurrentIndex(0);
    this->ui->c5Box->setCurrentIndex(10);
    this->ui->c6Box->setCurrentIndex(9);
    this->ui->c7Box->setCurrentIndex(2);
    this->ui->c8Box->setCurrentIndex(0);

    ui->statuLab->setPixmap(QPixmap(":/images/low.png"));

}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_startBtn_clicked()
{
    int htime = (int)(this->ui->d1SpinBox->value() * 1000);
    int ltime = (int)(this->ui->d2SpinBox->value() * 1000);

    mTimerThread.setTime(htime,ltime);

    mTimerThread.workStart();   //Start Thread
    mTimerThread.start();

    this->ui->startBtn->setEnabled(false);
    this->ui->d1SpinBox->setEnabled(false);
    this->ui->d2SpinBox->setEnabled(false);
    this->ui->c1Box->setEnabled(false);
    this->ui->c2Box->setEnabled(false);
    this->ui->c3Box->setEnabled(false);
    this->ui->c4Box->setEnabled(false);
    this->ui->c5Box->setEnabled(false);
    this->ui->c6Box->setEnabled(false);
    this->ui->c7Box->setEnabled(false);
    this->ui->c8Box->setEnabled(false);
    this->ui->label->setText("STATUS: Running");
}

void Dialog::on_stopBtn_clicked()
{
    mTimerThread.workStop();

    this->ui->startBtn->setEnabled(true);
    this->ui->d1SpinBox->setEnabled(true);
    this->ui->d2SpinBox->setEnabled(true);
    this->ui->c1Box->setEnabled(true);
    this->ui->c2Box->setEnabled(true);
    this->ui->c3Box->setEnabled(true);
    this->ui->c4Box->setEnabled(true);
    this->ui->c5Box->setEnabled(true);
    this->ui->c6Box->setEnabled(true);
    this->ui->c7Box->setEnabled(true);
    this->ui->c8Box->setEnabled(true);
    this->ui->label->setText("STATUS: Stop");
}


void Dialog::on_exitBtn_clicked()
{
    if(mTimerThread.isRunning())
    {
        mTimerThread.workStop();    // Stop Thread
        mTimerThread.terminate();
        mTimerThread.wait();
    }

    this->close();
}

void Dialog::comValue()
{
    int a = this->ui->c1Box->currentText().toInt();
    int b = this->ui->c2Box->currentText().toInt();
    int c = this->ui->c3Box->currentText().toInt();
    int d = this->ui->c4Box->currentText().toInt();
    double e = a * b * c * d * 0.1;
    this->ui->d1SpinBox->setValue(e);

    a = this->ui->c5Box->currentText().toInt();
    b = this->ui->c6Box->currentText().toInt();
    c = this->ui->c7Box->currentText().toInt();
    d = this->ui->c8Box->currentText().toInt();
    e = a * b * c * d * 0.1;
    this->ui->d2SpinBox->setValue(e);
}

void Dialog::setHValue(int value)
{
    //this->ui->hlcdNumber->display(value * 0.1);
}

void Dialog::setLValue(int value)
{
    //this->ui->llcdNumber->display(value * 0.1);
}

void Dialog::setSumValue(int value)
{
    this->ui->lcdNumber->display(value);
}

void Dialog::setHLStatus(int status)
{
   if(status)
       ui->statuLab->setPixmap(QPixmap(":/images/high.png"));
   else
       ui->statuLab->setPixmap(QPixmap(":/images/low.png"));
}
