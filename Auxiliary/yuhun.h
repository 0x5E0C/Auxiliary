#ifndef YUHUN_H
#define YUHUN_H

#include <QObject>
#include <QThread>
#include "config.h"
#include "counter.h"
#include "match.h"
#include "operations.h"
#include "delay.h"

class yuhun : public QThread
{
    Q_OBJECT
public:
    bool runflag;
    bool is_update_ui_thread;
    yuhun();
    yuhun(HWND hwnd,int mode,int threadid);
    void startTask();

protected:
    void run();

private:
    HWND handle;
    int mode_type;
    int id;
};

#endif // YUHUN_H
