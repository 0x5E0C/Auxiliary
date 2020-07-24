#include "match.h"
#include <QDebug>

double dpi;

match::match(HWND hwnd,control *ctrler)
{
    handle=hwnd;
    controller=ctrler;
    xframe=GetSystemMetrics(SM_CXFRAME);
    yframe=GetSystemMetrics(SM_CYFRAME);
    caption=GetSystemMetrics(SM_CYCAPTION);
}

/*函数功能:判断当前界面体力符合选定层数对应的体力*/
bool match::matchStrength(int mode)
{
    if(mode==single_mode)
    {
        if(compareResult(getScreenshot(0.8,1,0.8,1),single_mode)==guiInfo.matchtarget)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if(mode==team_mode)
    {
        if(compareResult(getScreenshot(0.9,1,0.9,1),team_mode)==guiInfo.matchtarget)
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

/*函数功能:判断当前界面挑战券符合选定层数对应的挑战券*/
bool match::matchProp()
{
    if(compareResult(getScreenshot(0.8,1,0.8,1),yyh_mode)==guiInfo.matchtarget)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*函数功能:返回最符合的结果*/
int match::compareResult(Mat img,int mode)
{
    QList<double> oldlist,resultlist;
    double mostmatch;
    int index;
    if(mode==single_mode)
    {
        oldlist.append(matchTemplateAndGetValue("single_6.png",img));
        oldlist.append(matchTemplateAndGetValue("single_9.png",img));
        oldlist.append(matchTemplateAndGetValue("single_12.png",img));
        resultlist=oldlist;
        std::sort(resultlist.begin(),resultlist.end());
        mostmatch=resultlist.at(resultlist.size()-1);
        if(mostmatch>0.9)
        {
            index=oldlist.indexOf(mostmatch);
            if(index==0)
            {
                return 6;
            }
            else if(index==1)
            {
                return 9;
            }
            else if(index==2)
            {
                return 12;
            }
        }
        else
        {
            return 0;
        }
    }
    else if(mode==yyh_mode)
    {
        oldlist.append(matchTemplateAndGetValue("tan.png",img));
        oldlist.append(matchTemplateAndGetValue("chen.png",img));
        oldlist.append(matchTemplateAndGetValue("chi.png",img));
        resultlist=oldlist;
        std::sort(resultlist.begin(),resultlist.end());
        mostmatch=resultlist.at(resultlist.size()-1);
        if(mostmatch>0.9)
        {
            index=oldlist.indexOf(mostmatch);
            if(index==0)
            {
                return -1;
            }
            else if(index==1)
            {
                return -2;
            }
            else if(index==2)
            {
                return -3;
            }
        }
        else
        {
            return 0;
        }
    }
    else if(mode==team_mode)
    {
        oldlist.append(matchTemplateAndGetValue("team_4.png",img));
        oldlist.append(matchTemplateAndGetValue("team_6.png",img));
        oldlist.append(matchTemplateAndGetValue("team_8.png",img));
        resultlist=oldlist;
        std::sort(resultlist.begin(),resultlist.end());
        mostmatch=resultlist.at(resultlist.size()-1);
        if(mostmatch>0.9)
        {
            index=oldlist.indexOf(mostmatch);
            if(index==0)
            {
                return 4;
            }
            else if(index==1)
            {
                return 6;
            }
            else if(index==2)
            {
                return 8;
            }
        }
        else
        {
            return 0;
        }
    }
    else if(mode==prepare_mode)
    {
        oldlist.append(matchTemplateAndGetValue("prepare.png",img));
        oldlist.append(matchTemplateAndGetValue("unprepare.png",img));
        std::sort(oldlist.begin(),oldlist.end());
        mostmatch=oldlist.at(oldlist.size()-1);
        if(mostmatch>0.8)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

/*函数功能:进行模板匹配并返回匹配位置*/
void match::matchTemplateAndReturnPos(QString filename,Mat target,int *x,int *y)
{
    Mat result;
    double min_val,max_val;
    cv::Point min_loc,max_loc;
    Mat templateimg=imread(filename);
    cv::matchTemplate(target,templateimg,result,CV_TM_CCOEFF_NORMED);
    minMaxLoc(result,&min_val,&max_val,&min_loc,&max_loc,Mat());
    if(max_val>=0.9)
    {
        *x=(max_loc.x+templateimg.rows/2)*dpi;
        *y=(max_loc.y+templateimg.cols/2)*dpi;

    }
    else
    {
        *x=-1;
        *y=-1;
    }
}

/*函数功能:进行模板匹配并返回匹配程度*/
double match::matchTemplateAndGetValue(QString filename,Mat target)
{
    Mat result;
    double min_val,max_val;
    cv::Point min_loc,max_loc,matchLoc;
    Mat templateimg=imread(filename);
    cv::matchTemplate(target,templateimg,result,CV_TM_CCOEFF_NORMED);
    minMaxLoc(result,&min_val,&max_val,&min_loc,&max_loc,Mat());
    return max_val;
}

/*函数功能:检测组队人数*/
int match::checkPersonCount()
{
    int personcount=1;
    if(matchTemplateAndGetValue("second.png",getScreenshot(0.3,0.6,0.2,0.6))<=0.8)
    {
        personcount+=1;
        if(matchTemplateAndGetValue("third.png",getScreenshot(0.7,1,0.2,0.6))<=0.8)
        {
            personcount+=1;
        }
    }
    return personcount;
}

/*函数功能:截取客户端界面(参数:左边界，右边界，上边界，下边界(比例))*/
Mat match::getScreenshot(float l=0,float r=1,float t=0,float b=1)
{
    HDC hDC;
    HDC hMemDC;
    RECT rc;
    BITMAP bitmap;
    HBITMAP hBitmap;
    HBITMAP hOldBmp;
    BITMAPINFOHEADER  bi;
    Mat src;
    int w,h;
    ::GetWindowRect(handle,&rc);
    w=rc.right-rc.left;
    h=rc.bottom-rc.top;
    if(h!=guiInfo.winheight)
    {
        emit promptmanager->updateShowArea("缩放窗口中...",INFO);
        if(!controller->adjustWindowsSize(h))
        {
            emit promptmanager->updateShowArea("缩放窗口失败!",ERR);
            emit promptmanager->errorevent();
        }
    }
    hDC=::GetWindowDC(handle);
    hMemDC=::CreateCompatibleDC(hDC);
    hBitmap=::CreateCompatibleBitmap(hDC,w,h);
    hOldBmp=(HBITMAP)::SelectObject(hMemDC,hBitmap);
    ::PrintWindow(handle,hMemDC,0);
    ::GetObject(hBitmap,sizeof(BITMAP),&bitmap);
    src.create(h,w,CV_8UC4);
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = w;
    bi.biHeight = -h;
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;
    GetDIBits(hMemDC,hBitmap,0,h,src.data,(BITMAPINFO *)&bi,DIB_RGB_COLORS);
    Mat graymat,graytarget;
    cvtColor(src,graymat,CV_BGR2GRAY);
    graytarget=graymat(cv::Rect(0,0,w/dpi,h/dpi));
    Mat contentimg=graytarget(cv::Rect(xframe,caption,graytarget.cols-2*xframe,graytarget.rows-caption-yframe));
    Mat imageROI=contentimg(cv::Rect(int(contentimg.cols*l),int(contentimg.rows*t),int(contentimg.cols*(r-l)),int(contentimg.rows*(b-t))));
    DeleteObject(hOldBmp);
    //SelectObject(hMemDC,hOldBmp);
    DeleteObject(hBitmap);
    DeleteObject(hMemDC);
    ReleaseDC(handle,hDC);
    return imageROI;
}

/*函数功能:返回图片文件完整路径*/
QString match::getImgPath(QString filename)
{
    return ":/"+guiInfo.resolution+"/"+guiInfo.resolution+"/"+filename;
}

/*函数功能:读取图片文件*/
Mat match::imread(QString filepath,int flag)
{
    QFile file(getImgPath(filepath));
    Mat m;
    if(file.open(QIODevice::ReadOnly))
    {
        qint64 sz=file.size();
        std::vector<uchar> buf(sz);
        file.read((char*)buf.data(),sz);
        m=imdecode(buf,flag);
    }
    Mat img;
    resize(m, img, Size(m.cols/dpi*1.25,m.rows/dpi*1.25),CV_INTER_AREA);
    return img;
}




