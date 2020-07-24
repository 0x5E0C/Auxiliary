#ifndef JUEXING_H
#define JUEXING_H

#include <QObject>
#include <QThread>
#include "config.h"
#include "counter.h"
#include "match.h"
#include "operations.h"
#include "delay.h"

class juexing : public QThread
{
    Q_OBJECT

public:
    bool runflag;
    bool is_leader_thread;
    bool is_update_ui_thread;
    juexing(HWND hwnd,int mode,int threadid);
    void startTask();

protected:
    void run();

private:
    HWND handle;
    int mode_type;
    int id;
};

#endif // JUEXING_H
