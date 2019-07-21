#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <timerthread.h>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
private:
    TimerThread mTimerThread;

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_startBtn_clicked();
    void on_exitBtn_clicked();  
    void comValue();
    void on_stopBtn_clicked();
    void setHValue(int value);
    void setLValue(int value);
    void setHLStatus(int status);
    void setSumValue(int value);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
