#include "yuhun.h"

yuhun::yuhun(HWND hwnd,int mode,int threadid)
{
    handle=hwnd;
    mode_type=mode;
    id=threadid;
}

/*函数功能:开始御魂模式程序流程*/
void yuhun::startTask()
{
    counter *countermanager=new counter();
    control *controller=new control(handle);
    match *matchmanager=new match(handle,controller);
    operations *operationsmanager=new operations(handle,controller,matchmanager);
    switch(guiInfo.mfloor)
    {
    case floor_1_10:
    case floor_11:
    case floor_rlzy1:
    case floor_rlzy2:
    case floor_rlzy3:
        countermanager->setProps(guiInfo.propcount);
        break;
    case floor_tan:
    case floor_chen:
    case floor_chi:
        countermanager->setTimes(guiInfo.challengetimes);
        break;
    default:
        break;
    }
    while(runflag)
    {
        if(countermanager->getType()==TIMES_TYPE)
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
        }
        else if(countermanager->getType()==PROPS_TYPE)
        {
            countermanager->decreaseProps();
            if(countermanager->getProps()<0)
            {
                emit promptmanager->updateShowArea("窗口"+QString::number(id)+":"+"已达设定樱饼上限",INFO);
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
                    emit promptmanager->updateUI(PROPS_TYPE,countermanager->getProps());
                }
                emit promptmanager->updateShowArea("窗口"+QString::number(id)+":"+"剩余樱饼数量"+QString::number(countermanager->getProps()),INFO);
            }
        }
        if(mode_type==single_mode)
        {
            if(matchmanager->matchStrength(single_mode))
            {
                controller->click(posInfo.common.single_challenge_pos.xpos,posInfo.common.single_challenge_pos.ypos);
            }
            else
            {
                emit promptmanager->updateShowArea("窗口"+QString::number(id)+":"+"未检测到副本"+guiInfo.floortext+"界面!",ERR);
                emit promptmanager->updateShowArea("窗口"+QString::number(id)+":"+"停止!",ERR);
                emit promptmanager->errorevent();
            }
        }
        else if(mode_type==yyh_mode)
        {
            if(matchmanager->matchProp())
            {
                controller->click(posInfo.common.single_challenge_pos.xpos,posInfo.common.single_challenge_pos.ypos);
            }
            else
            {
                emit promptmanager->updateShowArea("窗口"+QString::number(id)+":"+"未检测到副本"+guiInfo.floortext+"界面!",ERR);
                emit promptmanager->updateShowArea("窗口"+QString::number(id)+":"+"停止!",ERR);
                emit promptmanager->errorevent();
            }
        }
        else if(mode_type==team_mode)
        {
            if(matchmanager->matchTemplateAndGetValue("title.png",matchmanager->getScreenshot(0,0.25,0,0.15))>0.9)
            {
                if(matchmanager->matchTemplateAndGetValue("leaderflag1.png",matchmanager->getScreenshot(0.85,1,0.75,1))>0.8 || matchmanager->matchTemplateAndGetValue("leaderflag2.png",matchmanager->getScreenshot(0.85,1,0.75,1))>0.8)
                {
                    delayer->delayms(&runflag,2000);
                    int time=0;
                    while(runflag && matchmanager->checkPersonCount()!=guiInfo.person)
                    {
                        delayer->delayms(&runflag,500);
                        time++;
                        if(time==600)
                        {
                            emit promptmanager->updateShowArea("窗口"+QString::number(id)+":"+"组队超时!",ERR);
                            emit promptmanager->errorevent();
                            return;
                        }
                    }
                    if(matchmanager->matchStrength(team_mode))
                    {
                        controller->click(posInfo.common.team_challenge_pos.xpos,posInfo.common.team_challenge_pos.ypos);
                    }
                }
            }
            else
            {
                emit promptmanager->updateShowArea("窗口"+QString::number(id)+":"+"未检测到副本"+guiInfo.floortext+"界面!",ERR);
                emit promptmanager->updateShowArea("窗口"+QString::number(id)+":"+"停止!",ERR);
                emit promptmanager->errorevent();
            }
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
            delayer->delayms(&runflag,500);
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
        if(mode_type==single_mode)
        {
            while(runflag && !matchmanager->matchStrength(single_mode))
            {
                delayer->delayms(&runflag,500);
            }
        }
        else if(mode_type==yyh_mode)
        {
            while(runflag && !matchmanager->matchProp())
            {
                delayer->delayms(&runflag,500);
            }
        }
        else if(mode_type==team_mode)
        {
            while(runflag && matchmanager->matchTemplateAndGetValue("title.png",matchmanager->getScreenshot(0,0.25,0,0.15))<0.9)
            {
                delayer->delayms(&runflag,500);
            }
        }
        delayer->delayms(&runflag,500);
    }
    delete matchmanager;
    delete operationsmanager;
    delete controller;
    delete countermanager;
}

void yuhun::run()
{
    runflag=true;
    startTask();
}

