#ifndef MATCH_H
#define MATCH_H

#include <QString>
#include <QFile>
#include <QThread>
#include "config.h"
#include "control.h"

extern double dpi;

using namespace cv;
class control;
class match
{
public:
    match(HWND hwnd,control *ctrler);
    bool matchStrength(int mode);
    bool matchProp(int mode);
    bool matchLeader();
    quint8 matchCooperation();
    int compareResult(Mat img,int mode);
    void matchTemplateAndReturnPos(QString filename,Mat target,int *x,int *y,bool centermode=true);
    double matchTemplateAndGetValue(QString filename,Mat target);
    quint8 checkPersonCount();
    quint8 getMatchedJieJiePropsCount(Mat img);
    Mat getScreenshot(float l=0,float r=1,float t=0,float b=1,bool gray=true);
    QString getImgPath(QString filename);
    Mat imread(QString filepath,int flag=IMREAD_GRAYSCALE);

private:
    HWND handle;
    control *controller;
    int xframe,yframe,caption;
};

#endif // MATCH_H
