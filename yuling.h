#ifndef YULING_H
#define YULING_H

#include <QObject>
#include <QThread>
#include "config.h"
#include "counter.h"
#include "match.h"
#include "operations.h"
#include "delay.h"

class yuling : public QThread
{
    Q_OBJECT
public:
    bool runflag;
    bool is_update_ui_thread;
    yuling(HWND hwnd,int threadid);
    void startTask();

protected:
    void run();

private:
    HWND handle;
    int id;
};

#endif // YULING_H
