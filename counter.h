#ifndef PROPMANAGER_H
#define PROPMANAGER_H

#include "config.h"
#include "classify.h"

class counter
{
public:
    counter();
    void decreaseTimes();
    void decreaseProps();
    int getTimes();
    int getProps();
    void setTimes(int t);
    void setProps(int p);
    int getType();

private:
    int times;
    int props;
    int type;
};

#endif // PROPMANAGER_H
