#include "control.h"
#include <QDebug>

control::control(HWND hwnd)
{
    handle=hwnd;
}

/*函数功能:调整窗口大小*/
bool control::adjustWindowsSize(int h)
{
    if(h==guiInfo.winheight)
    {
        return true;
    }
    else
    {
        int screen_w,screen_h;
        RECT rect;
        screen_w=GetSystemMetrics(SM_CXSCREEN);
        screen_h=GetSystemMetrics(SM_CYSCREEN);
        if(guiInfo.resolution=="1440849")
        {
            MoveWindow(handle,int(0.5*(screen_w-1440)),int(0.5*(screen_h-849)),1440,849,false);
            QThread::msleep(500);
        }
        else if(guiInfo.resolution=="961579")
        {
            MoveWindow(handle,int(0.5*(screen_w-961)),int(0.5*(screen_h-579)),961,579,false);
            QThread::msleep(500);
        }
        QThread::msleep(500);
        GetWindowRect(handle,&rect);
        if((rect.bottom-rect.top)==guiInfo.winheight)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

/*函数功能:模拟鼠标点击(坐标输入)*/
void control::click(int x,int y)
{
    PostMessage(handle,WM_LBUTTONDOWN,0,x+y*65536);
    QThread::msleep(CLICK_TIME_INTERBAL);
    PostMessage(handle,WM_LBUTTONUP,0,x+y*65536);
}

/*函数功能:模拟鼠标点击(屏幕比例位置输入)*/
void control::click(double xproportion,double yproportion)
{
    RECT rc;
    ::GetWindowRect(handle,&rc);
    int xframe=GetSystemMetrics(SM_CXFRAME);
    int yframe=GetSystemMetrics(SM_CYFRAME);
    int caption=GetSystemMetrics(SM_CYCAPTION);
    int w=rc.right-rc.left-2*xframe;
    int h=rc.bottom-rc.top-yframe-caption;
    int x=w*xproportion;
    int y=h*yproportion;
    PostMessage(handle,WM_LBUTTONDOWN,0,x+y*65536);
    QThread::msleep(CLICK_TIME_INTERBAL);
    PostMessage(handle,WM_LBUTTONUP,0,x+y*65536);
}
