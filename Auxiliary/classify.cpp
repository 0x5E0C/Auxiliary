#include "classify.h"

bool *threadflaglist[MAX_PROCESS_COUNT];
int process_count;
struct guichoose guiInfo;
struct pos posInfo;
classify::classify(){}

/*函数功能:开始单人模式的识别程序*/
void classify::startSingleModeMatch()
{
    int mode_type;
    switch(guiInfo.challengetype)
    {
    case C_YUHUN:
        if(guiInfo.mfloor==floor_1_10 || guiInfo.mfloor==floor_rlzy1)
        {
            guiInfo.matchtarget=6;
        }
        else if(guiInfo.mfloor==floor_rlzy2)
        {
            guiInfo.matchtarget=9;
        }
        else if(guiInfo.mfloor==floor_11 || guiInfo.mfloor==floor_rlzy3)
        {
            guiInfo.matchtarget=12;
        }
        else if(guiInfo.mfloor==floor_tan)
        {
            guiInfo.matchtarget=-1;
        }
        else if(guiInfo.mfloor==floor_chen)
        {
            guiInfo.matchtarget=-2;
        }
        else if(guiInfo.mfloor==floor_chi)
        {
            guiInfo.matchtarget=-3;
        }
        if(guiInfo.matchtarget<0)
        {
            mode_type=yyh_mode;
        }
        else
        {
            mode_type=single_mode;
        }
        yuhun *updateUIThread;
        for(int i=0;i<process_count;i++)
        {
            yuhun *yuhunmanager=new yuhun(handle_list[i],mode_type,i);
            connect(yuhunmanager,SIGNAL(finished()),yuhunmanager,SLOT(deleteLater()));
            yuhunmanager->start();
            threadflaglist[i]=&(yuhunmanager->runflag);
            updateUIThread=yuhunmanager;
        }
        updateUIThread->is_update_ui_thread=true;
        break;
    default:
        break;
    }
}

/*函数功能:开始组队模式的识别程序*/
void classify::startTeamModeMatch()
{
    int mode_type;
    switch(guiInfo.challengetype)
    {
    case C_YUHUN:
        if(guiInfo.mfloor==floor_1_10 || guiInfo.mfloor==floor_rlzy1)
        {
            guiInfo.matchtarget=4;
        }
        else if(guiInfo.mfloor==floor_rlzy2)
        {
            guiInfo.matchtarget=6;
        }
        else if(guiInfo.mfloor==floor_11 || guiInfo.mfloor==floor_rlzy3)
        {
            guiInfo.matchtarget=8;
        }
        mode_type=team_mode;
        yuhun *updateUIThread;
        for(int i=0;i<process_count;i++)
        {
            yuhun *yuhunmanager=new yuhun(handle_list[i],mode_type,i);
            connect(yuhunmanager,SIGNAL(finished()),yuhunmanager,SLOT(deleteLater()));
            yuhunmanager->start();
            threadflaglist[i]=&(yuhunmanager->runflag);
            updateUIThread=yuhunmanager;
        }
        updateUIThread->is_update_ui_thread=true;
        break;
    default:
        break;
    }
}

/*函数功能:初始化各按钮位置信息*/
void classify::recordKeyPos()
{
    posInfo.common.single_challenge_pos.xpos=0.9107;
    posInfo.common.single_challenge_pos.ypos=0.8833;
    posInfo.common.team_challenge_pos.xpos=0.9532;
    posInfo.common.team_challenge_pos.ypos=0.9058;
    posInfo.common.friend_pos.xpos=0.0861;
    posInfo.common.friend_pos.ypos=0.0395;
    posInfo.common.chat_pos.xpos=0.1413;
    posInfo.common.chat_pos.ypos=0.0395;
    posInfo.common.finish_pos.xpos=0.5197;
    posInfo.common.finish_pos.ypos=0.9473;
}

/*函数功能:数据分类，根据结果分别开启识别程序*/
void classify::startTask()
{
    recordKeyPos();
    scanProcess();
    if(process_count==0)
    {
        emit promptmanager->errorevent();
        emit promptmanager->updateShowArea("未检测到进程",ERR);
        return;
    }
    if(guiInfo.isteam)
    {
        startTeamModeMatch();
    }
    else
    {
        startSingleModeMatch();
    }
    emit promptmanager->updateShowArea("开始",INFO);
}

/*函数功能:扫描所有客户端进程(不包括最小化的客户端)*/
void classify::scanProcess()
{
    QString title="阴阳师-网易游戏";
    HWND handle;
    int i=0;
    handle=FindWindowEx(NULL,NULL,NULL,title.toLocal8Bit());
    while(handle!=NULL)
    {
        if(!IsIconic(handle))
        {
            handle_list[i]=handle;
            i++;
        }
        handle=FindWindowEx(NULL,handle,NULL,title.toLocal8Bit());
    }
    process_count=i;
}




