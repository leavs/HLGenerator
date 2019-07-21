#ifndef TIMERTHREAD_H
#define TIMERTHREAD_H

#include <QThread>

#define HIGH "1"
#define LOW "0"

class TimerThread : public QThread
{
    Q_OBJECT

private:
    bool mStop = true;
    bool mPause = false;
    int mHtime,mLtime;
    int runTimes = 0;
    int b,l,t;
    int mGpioNum = 1;

protected:
    void run() Q_DECL_OVERRIDE;

public:
    TimerThread();
    void workStart();
    void workStop();

    void setTime(int htime,int ltime);
    void setGpioNum(int num);
    bool writeFile(const QString &filename, QString &value);
    void setGpioStatus(int gpionum, QString status);

signals:
    void oneWorkStop(int value);
    void gpioHL(int statu);
};

#endif // TIMERTHREAD_H
