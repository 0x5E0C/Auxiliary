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
            guiInfo.matchtarget=STRENGTH_6;
        }
        else if(guiInfo.mfloor==floor_rlzy2)
        {
            guiInfo.matchtarget=STRENGTH_9;
        }
        else if(guiInfo.mfloor==floor_11 || guiInfo.mfloor==floor_rlzy3)
        {
            guiInfo.matchtarget=STRENGTH_12;
        }
        else if(guiInfo.mfloor==floor_tan)
        {
            guiInfo.matchtarget=PROP_TAN;
        }
        else if(guiInfo.mfloor==floor_chen)
        {
            guiInfo.matchtarget=PROP_CHEN;
        }
        else if(guiInfo.mfloor==floor_chi)
        {
            guiInfo.matchtarget=PROP_CHI;
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
    case C_JUEXING:
        guiInfo.matchtarget=STRENGTH_6;
        juexing *juexing_updateUIThread;
        for(int i=0;i<process_count;i++)
        {
            juexing *juexingmanager=new juexing(handle_list[i],single_mode,i);
            connect(juexingmanager,SIGNAL(finished()),juexingmanager,SLOT(deleteLater()));
            juexingmanager->start();
            threadflaglist[i]=&(juexingmanager->runflag);
            juexing_updateUIThread=juexingmanager;
        }
        juexing_updateUIThread->is_update_ui_thread=true;
        break;
    case C_YULING:
        guiInfo.matchtarget=PROP_YULING;
        yuling *yuling_updateUIThread;
        for(int i=0;i<process_count;i++)
        {
            yuling *yulingmanager=new yuling(handle_list[i],i);
            connect(yulingmanager,SIGNAL(finished()),yulingmanager,SLOT(deleteLater()));
            yulingmanager->start();
            threadflaglist[i]=&(yulingmanager->runflag);
            yuling_updateUIThread=yulingmanager;
        }
        yuling_updateUIThread->is_update_ui_thread=true;
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
            guiInfo.matchtarget=STRENGTH_4;
        }
        else if(guiInfo.mfloor==floor_rlzy2)
        {
            guiInfo.matchtarget=STRENGTH_6;
        }
        else if(guiInfo.mfloor==floor_11 || guiInfo.mfloor==floor_rlzy3)
        {
            guiInfo.matchtarget=STRENGTH_8;
        }
        mode_type=team_mode;
        yuhun *yuhun_updateUIThread;
        for(int i=0;i<process_count;i++)
        {
            yuhun *yuhunmanager=new yuhun(handle_list[i],mode_type,i);
            connect(yuhunmanager,SIGNAL(finished()),yuhunmanager,SLOT(deleteLater()));
            yuhunmanager->start();
            threadflaglist[i]=&(yuhunmanager->runflag);
            yuhun_updateUIThread=yuhunmanager;
        }
        yuhun_updateUIThread->is_update_ui_thread=true;
        break;
    case C_JUEXING:
        guiInfo.matchtarget=STRENGTH_4;
        juexing *juexing_updateUIThread;
        for(int i=0;i<process_count;i++)
        {
            juexing *juexingmanager=new juexing(handle_list[i],team_mode,i);
            connect(juexingmanager,SIGNAL(finished()),juexingmanager,SLOT(deleteLater()));
            juexingmanager->start();
            threadflaglist[i]=&(juexingmanager->runflag);
            juexing_updateUIThread=juexingmanager;
        }
        juexing_updateUIThread->is_update_ui_thread=true;
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
    posInfo.common.prepare_pos.xpos=0.9191;
    posInfo.common.prepare_pos.ypos=0.7759;
    posInfo.common.friend_pos.xpos=0.0861;
    posInfo.common.friend_pos.ypos=0.0395;
    posInfo.common.chat_pos.xpos=0.1413;
    posInfo.common.chat_pos.ypos=0.0395;
    posInfo.common.finish_pos.xpos=0.5197;
    posInfo.common.finish_pos.ypos=0.9473;
    posInfo.cooperation.accept.xpos=0.6693;
    posInfo.cooperation.accept.ypos=0.5822;
    posInfo.cooperation.refuse.xpos=0.6162;
    posInfo.cooperation.refuse.ypos=0.1690;
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
    HWND handle;
    int i=0;
#ifdef USE_MINGW32
	handle = FindWindowEx(NULL, handle, NULL, title.toLocal8Bit());
#elif USE_MSVC
    handle=FindWindowEx(NULL,NULL,NULL,title.toStdWString().c_str());
#endif
    while(handle!=NULL)
    {
        if(!IsIconic(handle))
        {
            handle_list[i]=handle;
            i++;
        }
#ifdef USE_MINGW32
		handle = FindWindowEx(NULL, handle, NULL, title.toLocal8Bit());
#elif USE_MSVC
		handle = FindWindowEx(NULL, NULL, NULL, title.toStdWString().c_str());
#endif
    }
    process_count=i;
}




