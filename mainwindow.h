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
    void setTeamModeEnbale(bool state);
    void setUsePropEnbale(bool state);
    void setChallengeTimesEnbale(bool state);
    void setAddOtherOperationsEnable(bool state);
    void setButtomEnable(bool state);
    bool Check();
    void getWidgetsInfo();
    void getSystemDPI();

private:
    Ui::MainWindow *ui;
    classify *classifymanager;
    void View_Deinit();
    QString getCurrenttime(QString pattern);

private slots:
    void View_Init();
    void Start();
    void Pause();
    void Stop();
    void Change_challenge_mode(int floor);
    void Change_team_mode(int state);
    void addToShowArea(QString info,int infotype);
    void showErrorWin(QString errinfo,int flag=NO_KILL_PROCESS);
    void updateInfo(int mode,int info);
};
#endif // MAINWINDOW_H
