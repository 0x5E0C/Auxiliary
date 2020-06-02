#include "counter.h"

counter::counter()
{
    times=0;
    props=0;
}

/*函数功能:减少次数*/
void counter::decreaseTimes()
{
    times--;
}

/*函数功能:减少樱饼*/
void counter::decreaseProps()
{
    props-=guiInfo.matchtarget;
}

/*函数功能:获取剩余次数*/
int counter::getTimes()
{
    return times;
}

/*函数功能:调整剩余樱饼数量*/
int counter::getProps()
{
    return props;
}

/*函数功能:设置挑战次数*/
void counter::setTimes(int t)
{
    times=t;
    type=TIMES_TYPE;
}

/*函数功能:设置樱饼次数*/
void counter::setProps(int p)
{
    props=p;
    type=PROPS_TYPE;
}

/*函数功能:返回消耗类型(挑战次数或者樱饼)*/
int counter::getType()
{
    return type;
}
