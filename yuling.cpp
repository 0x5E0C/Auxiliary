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
    operations *operationsmanager=new operations(handle,controller,matchmanager);
    countermanager->setTimes(guiInfo.challengetimes);
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
                emit promptmanager->updateUI(TIMES_TYPE,countermanager->getTimes());
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
        delayer->delayms(&runflag,1500);
        while(runflag && matchmanager->matchTemplateAndGetValue("friend.png",matchmanager->getScreenshot(0.05,0.25,0,0.15))<0.9)
        {
            delayer->delayms(&runflag,500);
        }
        delayer->delayms(&runflag,2000);
        while(runflag && matchmanager->compareResult(matchmanager->getScreenshot(0.75,1,0.5,1),prepare_mode)==1)
        {
            delayer->delayms(&runflag,500);
        }
        if(runflag && guiInfo.addoperations)
        {
            operationsmanager->startOtherOperations(&runflag);
        }
        else
        {
            while(runflag && matchmanager->matchTemplateAndGetValue("time.png",matchmanager->getScreenshot(0.8,1,0,0.25))>0.8)
            {
                delayer->delayms(&runflag,500);
            }
        }
        while(runflag && matchmanager->matchTemplateAndGetValue("victory.png",matchmanager->getScreenshot(0.2,0.6,0,0.5))<0.8)
        {
            delayer->delayms(&runflag,100);
        }
        while(runflag && matchmanager->matchTemplateAndGetValue("prize.png",matchmanager->getScreenshot(0.3,0.75,0.45,1))<0.8)
        {
            delayer->delayms(&runflag,500);
            controller->click(posInfo.common.finish_pos.xpos,posInfo.common.finish_pos.ypos);
        }
        while(runflag && matchmanager->matchTemplateAndGetValue("prize.png",matchmanager->getScreenshot(0.3,0.75,0.45,1))>0.8)
        {
            delayer->delayms(&runflag,500);
            controller->click(posInfo.common.finish_pos.xpos,posInfo.common.finish_pos.ypos);
        }
        while(runflag && !matchmanager->matchProp(yuling_mode))
        {
            delayer->delayms(&runflag,500);
        }
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
