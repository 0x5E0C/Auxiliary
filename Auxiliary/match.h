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
    bool matchProp();
    int compareResult(Mat img,int mode);
    void matchTemplateAndReturnPos(QString filename,Mat target,int *x,int *y);
    double matchTemplateAndGetValue(QString filename,Mat target);
    int checkPersonCount();
    Mat getScreenshot(float l,float r,float t,float b);
    QString getImgPath(QString filename);
    Mat imread(QString filepath,int flag=IMREAD_GRAYSCALE);

private:
    HWND handle;
    control *controller;
    int xframe,yframe,caption;
};

#endif // MATCH_H
