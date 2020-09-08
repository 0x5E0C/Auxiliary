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
    void increaseJieJieProps(int count);
    int getTimes();
    int getProps();
    int getJieJieProp();
    void setTimes(int t);
    void setProps(int p);
    void setJieJieProps(int jp);
    int getType();

private:
    int times;
    int props;
    int jiejieprop;
    int type;
};

#endif // PROPMANAGER_H
