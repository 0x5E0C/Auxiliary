#include "operations.h"

operations::operations(HWND hwnd,control *ctrler,match *matcher,counter *counter)
{
    handle=hwnd;
    controller=ctrler;
    matchmanager=matcher;
    countermanager=counter;
}

/*函数功能:战斗操作*/
quint8 operations::fightOperations(bool *threadflag)
{
    delayer->delayms(threadflag,1500);
    while(*threadflag && matchmanager->compareResult(matchmanager->getScreenshot(0.75,1,0.5,1),prepare_mode)==NO_MATCH)
    {
        cooperationOperations();
        delayer->delayms(threadflag,SAMPLE_TIME);
    }
    while(*threadflag && matchmanager->compareResult(matchmanager->getScreenshot(0.75,1,0.5,1),prepare_mode))
    {
        cooperationOperations();
        delayer->delayms(threadflag,SAMPLE_TIME);
        if(guiInfo.autoprepare)
        {
            controller->click(posInfo.common.prepare_pos.xpos,posInfo.common.prepare_pos.ypos);
        }
    }
    if(*threadflag && guiInfo.addoperations)
    {
        startOtherOperations(threadflag);
    }
    else
    {
        while(*threadflag && matchmanager->matchTemplateAndGetValue("time.png",matchmanager->getScreenshot(0.8,1,0,0.25))>0.8)
        {
            cooperationOperations();
            delayer->delayms(threadflag,SAMPLE_TIME);
        }
    }
    while(*threadflag && matchmanager->compareResult(matchmanager->getScreenshot(0,1,0,1),fight_mode)==NO_MATCH)
    {
        cooperationOperations();
        delayer->delayms(threadflag,SAMPLE_TIME);
    }
    if(matchmanager->compareResult(matchmanager->getScreenshot(0.2,0.6,0,0.5),fight_mode)==FIGHT_VICTORY)
    {
        while(*threadflag && matchmanager->compareResult(matchmanager->getScreenshot(0.2,0.6,0,0.5),fight_mode)==FIGHT_VICTORY)
        {
            cooperationOperations();
            controller->click(posInfo.common.finish_pos.xpos,posInfo.common.finish_pos.ypos);
            delayer->delayms(threadflag,SAMPLE_TIME);
        }
    }
    else if(matchmanager->compareResult(matchmanager->getScreenshot(0.6,1,0.5,1),fight_mode)==FIGHT_FAIL)
    {
        while(*threadflag && matchmanager->compareResult(matchmanager->getScreenshot(0.6,1,0.5,1),fight_mode)==FIGHT_FAIL)
        {
            cooperationOperations();
            controller->click(posInfo.common.finish_pos.xpos,posInfo.common.finish_pos.ypos);
            delayer->delayms(threadflag,SAMPLE_TIME);
        }
        return 1;
    }
    while(*threadflag && matchmanager->matchTemplateAndGetValue("prize.png",matchmanager->getScreenshot(0.4,0.6,0.6,1))<0.8)
    {
        cooperationOperations();
        delayer->delayms(threadflag,SAMPLE_TIME);
        controller->click(posInfo.common.finish_pos.xpos,posInfo.common.finish_pos.ypos);
    }
    bool matchflag=true;
    while(*threadflag && matchmanager->matchTemplateAndGetValue("prize.png",matchmanager->getScreenshot(0.4,0.6,0.6,1))>0.8)
    {
        cooperationOperations();
        Mat cache=matchmanager->getScreenshot(0,1,0,1);
        if(guiInfo.stopwhenlimit)
        {
            if(matchmanager->matchTemplateAndGetValue("jiejieprop.png",cache)>0.8 && matchflag)
            {
                countermanager->increaseJieJieProps(matchmanager->getMatchedJieJiePropsCount(cache));
                matchflag=false;
            }
        }
        delayer->delayms(threadflag,SAMPLE_TIME);
        controller->click(posInfo.common.finish_pos.xpos,posInfo.common.finish_pos.ypos);
    }
    return 0;
}

/*函数功能:开始随机操作程序流程*/
void operations::startOtherOperations(bool *threadflag)
{
    int case_num;
    int find_xpos,find_ypos;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    case_num=qrand()%5;
    if(case_num==0)//friend
    {
        controller->click(posInfo.common.friend_pos.xpos,posInfo.common.friend_pos.ypos);
        delayer->delayms(&threadflag,2000);
        while(*threadflag && matchmanager->matchTemplateAndGetValue("unfinish.png",matchmanager->getScreenshot(0,0.25,0,0.25))>0.7)
        {
            cooperationOperations();
            delayer->delayms(&threadflag,SAMPLE_TIME);
        }
        matchmanager->matchTemplateAndReturnPos("close.png",matchmanager->getScreenshot(0,1,0,1),&find_xpos,&find_ypos);
        if(find_xpos!=-1 && find_ypos!=-1)
        {
            controller->click(find_xpos,find_ypos);
        }
    }
    if(case_num==1)//chat
    {
        controller->click(posInfo.common.chat_pos.xpos,posInfo.common.chat_pos.ypos);
        delayer->delayms(&threadflag,2000);
        matchmanager->matchTemplateAndReturnPos("world.png",matchmanager->getScreenshot(0,1,0,1),&find_xpos,&find_ypos);
        if(find_xpos!=-1 && find_ypos!=-1)
        {
            controller->click(find_xpos,find_ypos);
            delayer->delayms(&threadflag,1000);
        }
        while(*threadflag && matchmanager->matchTemplateAndGetValue("time.png",matchmanager->getScreenshot(0.8,1,0,0.25))>0.8)
        {
            cooperationOperations();
            delayer->delayms(&threadflag,SAMPLE_TIME);
        }
        matchmanager->matchTemplateAndReturnPos("packup.png",matchmanager->getScreenshot(0,1,0,1),&find_xpos,&find_ypos);
        if(find_xpos!=-1 && find_ypos!=-1)
        {
            controller->click(find_xpos,find_ypos);
        }
    }
    else
    {
        while(*threadflag && matchmanager->matchTemplateAndGetValue("time.png",matchmanager->getScreenshot(0.8,1,0,0.25))>0.8)
        {
            cooperationOperations();
            delayer->delayms(&threadflag,SAMPLE_TIME);
        }
    }
}

/*函数功能:对协作界面的操作*/
void operations::cooperationOperations()
{
    if(matchmanager->matchCooperation()==cooperation_accept)
    {
        controller->click(posInfo.cooperation.accept.xpos,posInfo.cooperation.accept.ypos);
    }
    else if(matchmanager->matchCooperation()==cooperation_refuse)
    {
        controller->click(posInfo.cooperation.refuse.xpos,posInfo.cooperation.refuse.ypos);
    }
}
