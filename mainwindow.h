#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QMessageBox>
#include <QString>
#include "config.h"
#include "classify.h"
#include "hotkey.h"
#include "match.h"
#include "prompt.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setTeamModeEnbale(int pages,bool state);
    bool check();
    void getWidgetsInfo();
    void getSystemDPI();

private:
    Ui::MainWindow *ui;
    classify *classifymanager;
    int freezeflag;
    void setAllWidgets(bool state);
    QString getCurrenttime(QString pattern);
    void freezeUI();
    void unfreezeUI();

private slots:
    void viewInit();
    void start();
    void pause();
    void stop();
    void changeChallengeMode(int floor);
    void changeTeamMode(int state);
    void addToShowArea(QString info,int infotype);
    void showErrorWin(QString errinfo,int flag=NO_KILL_PROCESS);
    void updateInfo(int mode,int info,int flag);
};
#endif // MAINWINDOW_H
