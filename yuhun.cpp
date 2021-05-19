#include "yuhun.h"

yuhun::yuhun(HWND hwnd,int mode,int threadid)
{
    handle=hwnd;
    mode_type=mode;
    id=threadid;
}

void yuhun::startTask()
{
    counter *countermanager=new counter();
    control *controller=new control(handle);
    match *matchmanager=new match(handle,controller);
    operations *operationsmanager=new operations(handle,controller,matchmanager,countermanager);
    countermanager->setJieJieProps(guiInfo.jiejiepropcount);
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
    if(mode_type==team_mode)
    {
        is_leader_thread=matchmanager->matchLeader();
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
                    emit promptmanager->updateUI(TIMES_TYPE,countermanager->getTimes(),C_YUHUN);
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
                    emit promptmanager->updateUI(PROPS_TYPE,countermanager->getProps(),C_YUHUN);
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
            if(matchmanager->matchProp(yyh_mode))
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
            if(is_leader_thread)
            {
                if(matchmanager->matchTemplateAndGetValue("title.png",matchmanager->getScreenshot(0,0.25,0,0.15))>0.9)
                {
                    delayer->delayms(&runflag,2000);
                    int time=0;
                    while(runflag && matchmanager->checkPersonCount()!=guiInfo.person)
                    {
                        delayer->delayms(&runflag,SAMPLE_TIME);
                        time++;
                        if(time==600)
                        {
                            emit promptmanager->updateShowArea("窗口"+QString::number(id)+":"+"组队超时!",ERR);
                            emit promptmanager->errorevent();
                            delete matchmanager;
                            delete operationsmanager;
                            delete controller;
                            delete countermanager;
                            return;
                        }
                    }
                    if(matchmanager->matchStrength(team_mode))
                    {
                        controller->click(posInfo.common.team_challenge_pos.xpos,posInfo.common.team_challenge_pos.ypos);
                    }
                }
                else
                {
                    emit promptmanager->updateShowArea("窗口"+QString::number(id)+":"+"未检测到副本"+guiInfo.floortext+"界面!",ERR);
                    emit promptmanager->updateShowArea("窗口"+QString::number(id)+":"+"停止!",ERR);
                    emit promptmanager->errorevent();
                }
            }
        }
        if(operationsmanager->fightOperations(&runflag) && !guiInfo.failstop)
        {
            emit promptmanager->updateShowArea("窗口"+QString::number(id)+":"+"战斗失败!已停止!",ERR);
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
        if(mode_type==single_mode)
        {
            while(runflag && !matchmanager->matchStrength(single_mode))
            {
                delayer->delayms(&runflag,SAMPLE_TIME);
            }
        }
        else if(mode_type==yyh_mode)
        {
            while(runflag && !matchmanager->matchProp(yyh_mode))
            {
                delayer->delayms(&runflag,SAMPLE_TIME);
            }
        }
        else if(mode_type==team_mode)
        {
            while(runflag && matchmanager->matchTemplateAndGetValue("title.png",matchmanager->getScreenshot(0,0.25,0,0.15))<0.9)
            {
                delayer->delayms(&runflag,SAMPLE_TIME);
            }
        }
        delayer->delayms(&runflag,1000);
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
