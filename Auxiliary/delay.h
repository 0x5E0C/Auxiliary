#ifndef DELAY_H
#define DELAY_H

#include <QThread>
#include "config.h"

class delay;
extern delay *delayer;

class delay
{
public:
    delay();
    void delayms(bool *threadflag,int ms);
    void delayms(bool **threadflag,int ms);
};

#endif // DELAY_H
