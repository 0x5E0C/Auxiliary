#ifndef PROMPT_H
#define PROMPT_H

#include <QObject>
#include "config.h"

class prompt;
extern prompt *promptmanager;

class prompt : public QObject
{
    Q_OBJECT
public:
    explicit prompt();

signals:
    void updateShowArea(QString info,int infotype);
    void errorevent();
    void failevent();
    void finishevent();
    void updateUI(int mode,int info,int flag);
};

#endif // PROMPT_H
