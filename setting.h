#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include <QMessageBox>
#include <QDir>
#include "update.h"
#include "config.h"

namespace Ui {
class setting;
}

class setting : public QWidget
{
    Q_OBJECT

signals:
    void destroywindows(QVector<quint8> info);
    void restart();

public:
    explicit setting(QWidget *parent = nullptr);
    ~setting();
    void loadSettingInfo();
    void setArgs();
    void freezeUI();
    void unfreezeUI();

private:
    Ui::setting *ui;
    QVector<quint8> widgetsinfo;
    class update *updatewindow=new class update();
    void viewInit();
    bool check();
    void saveSettingInfo();

private slots:
    void getWidgetsInfo();
    void changeEditLimitEnable(int state);
    void sendRestartProgramSignal();
    void showUpdateWindow();
};

#endif // SETTING_H
