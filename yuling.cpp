#include "yuling.h"

yuling::yuling(HWND hwnd,int threadid)
{
    handle=hwnd;
    id=threadid;
}

void yuling::startTask()
{
    counter *countermanager=new counter();
    control *controller=new control(handle);
    match *matchmanager=new match(handle,controller);
    operations *operationsmanager=new operations(handle,controller,matchmanager,countermanager);
    countermanager->setTimes(guiInfo.challengetimes);
    countermanager->setJieJieProps(guiInfo.jiejiepropcount);
    while(runflag)
    {
        countermanager->decreaseTimes();
        if(countermanager->getTimes()<0)
        {
            emit promptmanager->updateShowArea("窗口"+QString::number(id)+":"+"已达设定次数上限",INFO);
            emit promptmanager->finishevent();
            delete matchmanager;
            delete operationsmanager;
            delete controller;
            delete countermanager;
            return;
        }
        else
        {
            if(is_update_ui_thread)
            {
                emit promptmanager->updateUI(TIMES_TYPE,countermanager->getTimes(),C_YULING);
            }
            emit promptmanager->updateShowArea("窗口"+QString::number(id)+":"+"开始第"+QString::number(guiInfo.challengetimes-countermanager->getTimes())+"次挑战",INFO);
        }
        if(matchmanager->matchProp(yuling_mode))
        {
            controller->click(posInfo.common.single_challenge_pos.xpos,posInfo.common.single_challenge_pos.ypos);
        }
        else
        {
            emit promptmanager->updateShowArea("窗口"+QString::number(id)+":"+"未检测到副本"+guiInfo.floortext+"界面!",ERR);
            emit promptmanager->updateShowArea("窗口"+QString::number(id)+":"+"停止!",ERR);
            emit promptmanager->errorevent();
        }
        if(operationsmanager->fightOperations(&runflag) && !guiInfo.failstop)
        {

            emit promptmanager->failevent();
            delete matchmanager;
            delete operationsmanager;
            delete controller;
            delete countermanager;
            return;
        }
        if(guiInfo.stopwhenlimit)
        {
            if(countermanager->getJieJieProp()>=30)
            {
                emit promptmanager->updateShowArea("窗口"+QString::number(id)+":"+"结界突破券达到上限!已停止!",INFO);
                emit promptmanager->finishevent();
                delete matchmanager;
                delete operationsmanager;
                delete controller;
                delete countermanager;
                return;
            }
        }
        while(runflag && !matchmanager->matchProp(yuling_mode))
        {
            delayer->delayms(&runflag,SAMPLE_TIME);
            if(!guiInfo.failstop)
            {
                controller->click(posInfo.common.finish_pos.xpos,posInfo.common.finish_pos.ypos);
            }
        }
        delayer->delayms(&runflag,1000);
    }
    delete matchmanager;
    delete operationsmanager;
    delete controller;
    delete countermanager;
}

void yuling::run()
{
    runflag=true;
    startTask();
}
