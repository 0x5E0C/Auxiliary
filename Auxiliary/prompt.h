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
    void finishevent();
    void updateUI(int mode,int info);
};

#endif // PROMPT_H
