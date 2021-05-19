#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <QTime>
#include "config.h"
#include "control.h"
#include "match.h"
#include "delay.h"
#include "counter.h"

class control;
class match;
class counter;
class operations
{
public:
    operations(HWND hwnd,control *ctrler,match *matcher,counter *counter);
    quint8 fightOperations(bool *threadflag);
    void startOtherOperations(bool *threadflag);
    void cooperationOperations();

private:
    HWND handle;
    control *controller;
    match *matchmanager;
    counter *countermanager;
};

#endif // OPERATIONS_H
