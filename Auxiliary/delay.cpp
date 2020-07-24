#include "delay.h"

delay *delayer=new delay();

delay::delay(){}

/*函数功能:延时函数(参数:线程运行状态标志，毫秒)*/
void delay::delayms(bool *threadflag,int ms)
{
    int times=ms/BASE_TIME;
    while(times && *threadflag)
    {
        QThread::msleep(BASE_TIME);
        times--;
    }
    QThread::msleep(ms%BASE_TIME);
}

/*函数功能:延时函数(参数:线程运行状态标志，毫秒)*/
void delay::delayms(bool **threadflag,int ms)
{
    int times=ms/BASE_TIME;
    while(times && **threadflag)
    {
        QThread::msleep(BASE_TIME);
        times--;
    }
    QThread::msleep(ms%BASE_TIME);
}
