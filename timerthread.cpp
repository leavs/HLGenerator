#include "timerthread.h"
#include <QFile>
#include <QIODevice>
#include <QDebug>
#include <QTime>

TimerThread::TimerThread()
{
}

void TimerThread::run()
{
    while(!mStop)
    {
        while(!mPause)
        {
            //writeFile("/dev/chipsee-gpio1","1");
            setGpioStatus(mGpioNum,HIGH);
            msleep(mHtime);
            if(!mLtime)
            {
                //writeFile("/dev/chipsee-gpio1","0");
                setGpioStatus(mGpioNum,LOW);
                mPause = true;
                break;
            }
            //writeFile("/dev/chipsee-gpio1","0");
            setGpioStatus(mGpioNum,LOW);
            msleep(mLtime);

            runTimes++;
            emit oneWorkStop(runTimes);
        }

        qDebug() <<"Thread Pause";
        msleep(500);
    }
    quit();
    qDebug() <<"Thread Quit";
}

void TimerThread::workStart()
{
    mPause = false;
    mStop = false;
}

void TimerThread::workStop()
{
    mPause = true;
    mStop = true;
}

void TimerThread::setTime(int htime, int ltime)
{
    mHtime = htime;
    mLtime = ltime;
}

void TimerThread::setGpioNum(int num)
{
    mGpioNum = num;
}

bool TimerThread::writeFile(const QString &filename, QString &value)
{
    QFile mFile(filename);
    if(!mFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream mTextStream(&mFile);
    mTextStream << value;
    mFile.close();
    return true;
}

void TimerThread::setGpioStatus(int gpionum, QString status)
{
    bool ret;
    QString path = QString::asprintf("/dev/chipsee-gpio%d",gpionum);
    ret = writeFile(path,status);
    if (ret)
        qDebug() << "writeFile success";
    else
        qDebug() << "writeFile faile";

    emit gpioHL(status.toInt());
}
