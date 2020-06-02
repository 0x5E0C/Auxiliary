#ifndef CONTROL_H
#define CONTROL_H

#include "config.h"
#include "classify.h"

class control
{
public:
    control(HWND hwnd);
    bool adjustWindowsSize(int h);
    void click(int x,int y);
    void click(double xproportion,double yproportion);

private:
    HWND handle;

};

#endif // CONTROL_H
