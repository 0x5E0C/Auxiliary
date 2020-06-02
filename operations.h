#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <QTime>
#include "config.h"
#include "control.h"
#include "match.h"
#include "delay.h"

class control;
class match;
class operations
{
public:
    operations(HWND hwnd,control *ctrler,match *matcher);
    void startOtherOperations(bool *threadflag);

private:
    HWND handle;
    control *controller;
    match *matchmanager;
};

#endif // OPERATIONS_H
