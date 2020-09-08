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
bool match::matchProp(int mode)
{
    if(compareResult(getScreenshot(0.8,1,0.8,1),mode)==guiInfo.matchtarget)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*函数功能:判断是否为队长*/
bool match::matchLeader()
{
    if(matchTemplateAndGetValue("leaderflag1.png",getScreenshot(0.85,1,0.75,1))>0.9 || matchTemplateAndGetValue("leaderflag2.png",getScreenshot(0.85,1,0.75,1))>0.9)
    {
        return true;
    }
    return false;
}

/*函数功能:判断当前界面是否有所选协作*/
quint8 match::matchCooperation()
{
    if((guiInfo.magatama30 && matchTemplateAndGetValue("magatama30.png",getScreenshot(0.36,0.69,0.50,0.80))>0.9) ||
       (guiInfo.strength30 && matchTemplateAndGetValue("strength30.png",getScreenshot(0.36,0.69,0.50,0.80))>0.9) ||
       (guiInfo.gold2w && matchTemplateAndGetValue("gold2w.png",getScreenshot(0.36,0.69,0.50,0.80))>0.9) ||
       (guiInfo.gold3w && matchTemplateAndGetValue("gold3w.png",getScreenshot(0.36,0.69,0.50,0.80))>0.9))
    {
        return cooperation_accept;
    }
    else if(matchTemplateAndGetValue("magatama30.png",getScreenshot(0.36,0.69,0.50,0.80))>0.9 ||
            matchTemplateAndGetValue("strength30.png",getScreenshot(0.36,0.69,0.50,0.80))>0.9 ||
            matchTemplateAndGetValue("gold2w.png",getScreenshot(0.36,0.69,0.50,0.80))>0.9 ||
            matchTemplateAndGetValue("gold3w.png",getScreenshot(0.36,0.69,0.50,0.80))>0.9)
    {
        return cooperation_refuse;
    }
    return no_find;
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
                return STRENGTH_6;
            }
            else if(index==1)
            {
                return STRENGTH_9;
            }
            else if(index==2)
            {
                return STRENGTH_12;
            }
        }
        else
        {
            return NO_MATCH;
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
                return STRENGTH_4;
            }
            else if(index==1)
            {
                return STRENGTH_6;
            }
            else if(index==2)
            {
                return STRENGTH_8;
            }
        }
        else
        {
            return NO_MATCH;
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
                return PROP_TAN;
            }
            else if(index==1)
            {
                return PROP_CHEN;
            }
            else if(index==2)
            {
                return PROP_CHI;
            }
        }
        else
        {
            return NO_MATCH;
        }
    }
    else if(mode==yuling_mode)
    {
        if(matchTemplateAndGetValue("yuling.png",img)>0.8)
        {
            return PROP_YULING;
        }
        else
        {
            return NO_MATCH;
        }
        return NO_MATCH;
    }
    else if(mode==prepare_mode)
    {
        oldlist.append(matchTemplateAndGetValue("prepare.png",img));
        oldlist.append(matchTemplateAndGetValue("unprepare.png",img));
        std::sort(oldlist.begin(),oldlist.end());
        mostmatch=oldlist.at(oldlist.size()-1);
        if(mostmatch>0.8)
        {
            return GOOD_MATCH;
        }
        else
        {
            return NO_MATCH;
        }
    }
    else if(mode==fight_mode)
    {
        oldlist.append(matchTemplateAndGetValue("victory.png",img));
        oldlist.append(matchTemplateAndGetValue("fail.png",img));
        resultlist=oldlist;
        std::sort(resultlist.begin(),resultlist.end());
        mostmatch=resultlist.at(resultlist.size()-1);
        if(mostmatch>0.8)
        {
            index=oldlist.indexOf(mostmatch);
            if(index==0)
            {
                return FIGHT_VICTORY;
            }
            else if(index==1)
            {
                return FIGHT_FAIL;
            }
        }
        else
        {
            return NO_MATCH;
        }
    }
    return NO_MATCH;
}

/*函数功能:进行模板匹配并返回匹配位置*/
void match::matchTemplateAndReturnPos(QString filename,Mat target,int *x,int *y,bool centermode)
{
    Mat result;
    double min_val,max_val;
    Point min_loc,max_loc;
    Mat templateimg=imread(filename);
    matchTemplate(target,templateimg,result,CV_TM_CCOEFF_NORMED);
    minMaxLoc(result,&min_val,&max_val,&min_loc,&max_loc,Mat());
    if(max_val>=0.9)
    {
        if(centermode)
        {
            *x=(max_loc.x+templateimg.rows/2)*dpi;
            *y=(max_loc.y+templateimg.cols/2)*dpi;
        }
        else
        {
            *x=max_loc.x*dpi;
            *y=max_loc.y*dpi;
        }
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
    Point min_loc,max_loc,matchLoc;
    Mat templateimg=imread(filename);
    matchTemplate(target,templateimg,result,CV_TM_CCOEFF_NORMED);
    minMaxLoc(result,&min_val,&max_val,&min_loc,&max_loc,Mat());
    return max_val;
}

/*函数功能:检测组队人数*/
quint8 match::checkPersonCount()
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

/*函数功能:获取得到的结界突破券数量*/
quint8 match::getMatchedJieJiePropsCount(Mat img)
{
    Mat mask=imread("mask.png");
    quint8 count=0;
    int x,y;
    while(1)
    {
        if(matchTemplateAndGetValue("jiejieprop.png",img)>0.8)
        {
            count++;
            matchTemplateAndReturnPos("jiejieprop.png",img,&x,&y,false);
            Rect rect=Rect(x/dpi,y/dpi,mask.cols,mask.rows);
            mask.copyTo(img(rect));
        }
        else
        {
            break;
        }
    }
    return count;
}

/*函数功能:截取客户端界面(参数:左边界，右边界，上边界，下边界(比例))*/
Mat match::getScreenshot(float l,float r,float t,float b,bool gray)
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
    Mat contentimg;
    if(gray)
    {
        Mat graymat,graytarget;
        cvtColor(src,graymat,CV_BGR2GRAY);
        graytarget=graymat(cv::Rect(0,0,w/dpi,h/dpi));
        contentimg=graytarget(cv::Rect(xframe,caption,graytarget.cols-2*xframe,graytarget.rows-caption-yframe));
    }
    else
    {
        Mat imgmat;
        imgmat=src(cv::Rect(0,0,w/dpi,h/dpi));
        contentimg=imgmat(cv::Rect(xframe,caption,imgmat.cols-2*xframe,imgmat.rows-caption-yframe));
    }
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
    resize(m,img,Size(m.cols/dpi*1.25,m.rows/dpi*1.25),CV_INTER_AREA);
    return img;
}




