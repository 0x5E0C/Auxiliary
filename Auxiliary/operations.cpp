#include "operations.h"

operations::operations(HWND hwnd,control *ctrler,match *matcher)
{
    handle=hwnd;
    controller=ctrler;
    matchmanager=matcher;
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
            delayer->delayms(&threadflag,500);
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
            delayer->delayms(&threadflag,500);
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
            delayer->delayms(&threadflag,500);
        }
    }
}
