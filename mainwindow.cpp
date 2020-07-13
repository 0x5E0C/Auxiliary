#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    hotkeymanager->setHook();
    setWindowFlags(0);
    setFixedSize(this->width(),this->height());
    setWindowTitle("辅助器");
    View_Init();
    getSystemDPI();
    connect(ui->chooseFloor,SIGNAL(currentIndexChanged(int)),this,SLOT(Change_challenge_mode(int)));
    connect(ui->isTeamMode,SIGNAL(stateChanged(int)),this,SLOT(Change_team_mode(int)));
    connect(ui->button_start,SIGNAL(clicked()),this,SLOT(Start()));
    connect(ui->button_pause,SIGNAL(clicked()),this,SLOT(Pause()));
    connect(ui->button_stop,SIGNAL(clicked()),this,SLOT(Stop()));
    connect(hotkeymanager,SIGNAL(hotkeyevent()),this,SLOT(Pause()));
    connect(promptmanager,SIGNAL(errorevent()),this,SLOT(Stop()));
    connect(promptmanager,SIGNAL(updateShowArea(QString,int)),this,SLOT(addToShowArea(QString,int)));
    connect(promptmanager,SIGNAL(finishevent()),this,SLOT(Stop()));
    connect(promptmanager,SIGNAL(updateUI(int,int)),this,SLOT(updateInfo(int,int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*函数功能:开启识别功能*/
void MainWindow::Start()
{
    if(Check())
    {
        getWidgetsInfo();
        ui->chooseFloor->setEnabled(false);
        ui->isTeamMode->setEnabled(false);
        ui->editPersonCount->setEnabled(false);
        ui->editPropCount->setEnabled(false);
        ui->editChallengetimes->setEnabled(false);
        ui->isAddOtherOperations->setEnabled(false);
        ui->button_start->setEnabled(false);
        ui->resolution1->setEnabled(false);
        ui->resolution2->setEnabled(false);
        addToShowArea("即将开始!",INFO);
        addToShowArea("读取设置中...",INFO);
        addToShowArea("已选择副本："+ui->chooseFloor->currentText(),INFO);
        classifymanager=new classify();
        classifymanager->startTask();
    }
}

/*函数功能:暂停识别，不使能ui，防止误操作*/
void MainWindow::Pause()
{
    ui->button_start->setEnabled(true);
    for(int i=0;i<process_count;i++)
    {
        *threadflaglist[i]=false;
    }
    addToShowArea("已暂停!",INFO);
}

/*函数功能:停止识别，使能ui*/
void MainWindow::Stop()
{
    Change_challenge_mode(ui->chooseFloor->currentIndex());
    ui->chooseFloor->setEnabled(true);
    ui->button_start->setEnabled(true);
    ui->resolution1->setEnabled(true);
    ui->resolution2->setEnabled(true);
    for(int i=0;i<process_count;i++)
    {
        *threadflaglist[i]=false;
    }
}

/*函数功能:根据选择的层数改变ui*/
void MainWindow::Change_challenge_mode(int floor)
{
    if(floor==not_choose)
    {
        setTeamModeEnbale(false);
        setUsePropEnbale(false);
        setChallengeTimesEnbale(false);
        setAddOtherOperationsEnable(false);
    }
    else if(floor==floor_1_10 || floor==floor_11 || floor==floor_rlzy1 || floor==floor_rlzy2 || floor==floor_rlzy3)
    {
        setTeamModeEnbale(true);
        setUsePropEnbale(true);
        setChallengeTimesEnbale(false);
        setAddOtherOperationsEnable(true);
    }
    else if(floor==floor_tan || floor==floor_chen || floor==floor_chi)
    {
        setTeamModeEnbale(false);
        setUsePropEnbale(false);
        setChallengeTimesEnbale(true);
        setAddOtherOperationsEnable(true);
    }
}

/*函数功能:根据是否选择组队模式改变ui*/
void MainWindow::Change_team_mode(int state)
{
    if(state==Qt::Checked)
    {
        ui->label_personcount->setEnabled(true);
        ui->editPersonCount->setEnabled(true);
    }
    else if(state==Qt::Unchecked)
    {
        ui->label_personcount->setEnabled(false);
        ui->editPersonCount->setEnabled(false);
    }
}

/*函数功能:添加信息提示到信息提示区*/
void MainWindow::addToShowArea(QString info,int infotype)
{
    ui->showInfoArea->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
    if(infotype==ERR)
    {
        ui->showInfoArea->setTextColor(QColor(255,0,0));
    }
    else if(infotype==INFO)
    {
        ui->showInfoArea->setTextColor(QColor(127,255,0));
    }
    ui->showInfoArea->insertPlainText(getCurrenttime("hh:mm:ss")+"\t"+info+"\n");
    ui->showInfoArea->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
}

/*函数功能:显示错误窗口*/
void MainWindow::showErrorWin(QString errinfo,int flag)
{
    QMessageBox::critical(this,"错误",errinfo);
    if(flag)
    {
        DWORD pid = GetCurrentProcessId();
        QString command="tskill "+QString::number(pid);
        system(command.toLocal8Bit());
    }
}

/*函数功能:检查ui交互数据*/
bool MainWindow::Check()
{
    int person_count,prop_count,challengetimes,floor;
    person_count=ui->editPersonCount->text().toInt();
    prop_count=ui->editPropCount->text().toInt();
    challengetimes=ui->editChallengetimes->text().toInt();
    floor=ui->chooseFloor->currentIndex();
    if(ui->chooseFloor->currentIndex()==not_choose)
    {
        QMessageBox::critical(this,"错误","未选择副本!");
        addToShowArea("错误：未选择副本!",ERR);
        return false;
    }
    else
    {
        if(ui->isTeamMode->isEnabled() && ui->isTeamMode->checkState()==Qt::Checked && (person_count>3 || person_count<=1))
        {
            QMessageBox::critical(this,"错误","组队人数输入错误!");
            addToShowArea("错误：组队人数输入应在1~3范围内!",ERR);
            return false;
        }
        if((floor==floor_1_10 || floor==floor_11 || floor==floor_rlzy1 || floor==floor_rlzy2 || floor==floor_rlzy3) && ui->editPropCount->isEnabled() && prop_count<=0)
        {
            QMessageBox::critical(this,"错误","樱饼数量输入错误!");
            addToShowArea("错误：樱饼数量输入应大于0!",ERR);
            return false;
        }
        if((floor==floor_tan || floor==floor_chen || floor==floor_chi) && ui->editChallengetimes->isEnabled() && challengetimes<=0)
        {
            QMessageBox::critical(this,"错误","挑战次数输入错误!");
            addToShowArea("错误：挑战次数输入应大于0!",ERR);
            return false;
        }
        return true;
    }
}

/*函数功能:获得当前时间，用于提示信息*/
QString MainWindow::getCurrenttime(QString pattern)
{
    QDateTime currenttime;
    currenttime= QDateTime::currentDateTime();
    return currenttime.toString(pattern);
}

/*函数功能:使能所有ui*/
void MainWindow::View_Init()
{
    setTeamModeEnbale(false);
    setUsePropEnbale(false);
    setChallengeTimesEnbale(false);
    setAddOtherOperationsEnable(false);
    setButtomEnable(true);
    ui->chooseFloor->setEnabled(true);
}

/*函数功能:失能所有ui*/
void MainWindow::View_Deinit()
{
    setTeamModeEnbale(false);
    setUsePropEnbale(false);
    setChallengeTimesEnbale(false);
    setAddOtherOperationsEnable(false);
    setButtomEnable(false);
    ui->chooseFloor->setEnabled(false);
}

/*函数功能:控制组队相关ui*/
void MainWindow::setTeamModeEnbale(bool state)
{
    if(state)
    {
        ui->isTeamMode->setEnabled(true);
        if(ui->isTeamMode->checkState()==Qt::Checked)
        {
            ui->label_personcount->setEnabled(true);
            ui->editPersonCount->setEnabled(true);
        }
        else if(ui->isTeamMode->checkState()==Qt::Unchecked)
        {
            ui->label_personcount->setEnabled(false);
            ui->editPersonCount->setEnabled(false);
        }
    }
    else
    {
        ui->isTeamMode->setEnabled(false);
        ui->label_personcount->setEnabled(false);
        ui->editPersonCount->setEnabled(false);
    }
}

/*函数功能:控制樱饼相关ui*/
void MainWindow::setUsePropEnbale(bool state)
{
    if(state)
    {
        ui->label_propcount->setEnabled(true);
        ui->editPropCount->setEnabled(true);
    }
    else
    {
        ui->label_propcount->setEnabled(false);
        ui->editPropCount->setEnabled(false);
    }
}

/*函数功能:控制次数相关ui*/
void MainWindow::setChallengeTimesEnbale(bool state)
{
    if(state)
    {
        ui->label_challengetimes->setEnabled(true);
        ui->editChallengetimes->setEnabled(true);
    }
    else
    {
        ui->label_challengetimes->setEnabled(false);
        ui->editChallengetimes->setEnabled(false);
    }
}

/*函数功能:控制添加其他操作相关ui*/
void MainWindow::setAddOtherOperationsEnable(bool state)
{
    if(state)
    {
        ui->isAddOtherOperations->setEnabled(true);
    }
    else
    {
        ui->isAddOtherOperations->setEnabled(false);
    }
}

/*函数功能:控制按钮相关ui*/
void MainWindow::setButtomEnable(bool state)
{
    if(state)
    {
        ui->button_start->setEnabled(true);
        ui->button_pause->setEnabled(true);
        ui->button_stop->setEnabled(true);
    }
    else
    {
        ui->button_start->setEnabled(false);
        ui->button_pause->setEnabled(false);
        ui->button_stop->setEnabled(false);
    }
}

/*函数功能:获取所有ui交互信息*/
void MainWindow::getWidgetsInfo()
{
    guiInfo.challengetype=ui->pages->currentIndex();
    guiInfo.mfloor=ui->chooseFloor->currentIndex();
    if(ui->isTeamMode->isChecked() && ui->isTeamMode->isEnabled())
    {
        guiInfo.isteam=true;
        guiInfo.person=ui->editPersonCount->text().toInt();
    }
    else
    {
        guiInfo.isteam=false;
        guiInfo.person=-1;
    }
    if(ui->editPropCount->isEnabled())
    {
        guiInfo.propcount=ui->editPropCount->text().toInt();
    }
    else
    {
        guiInfo.propcount=-1;
    }
    if(ui->editChallengetimes->isEnabled())
    {
        guiInfo.challengetimes=ui->editChallengetimes->text().toInt();
    }
    else
    {
        guiInfo.challengetimes=-1;
    }
    if(ui->isAddOtherOperations->isChecked())
    {
        guiInfo.addoperations=true;
    }
    else
    {
        guiInfo.addoperations=false;
    }
    if(ui->resolution1->isChecked())
    {
        guiInfo.resolution="1440849";
        guiInfo.winheight=849;
    }
    else if(ui->resolution2->isChecked())
    {
        guiInfo.resolution="961579";
        guiInfo.winheight=579;
    }
    guiInfo.floortext=ui->chooseFloor->currentText();
}

/*函数功能:获取系统dpi*/
void MainWindow::getSystemDPI()
{

    HDC desktopDc = GetDC(NULL);
    int verticalDPI = GetDeviceCaps(desktopDc,LOGPIXELSY);
    switch (verticalDPI)
    {
    case 96:
        dpi=1;
        break;
    case 120:
        dpi=1.25;
        break;
    case 144:
        dpi=1.5;
        QMessageBox::warning(this,"警告","当前显示比例为150%,某些图标可能识别不准确,建议调至(100%或125%)!\n详情请查看帮助或帮助文档!");
        break;
    case 168:
        dpi=1.75;
        QMessageBox::warning(this,"警告","当前显示比例为175%,某些图标可能识别不准确,建议调至(100%或125%)!\n详情请查看帮助或帮助文档!");
        break;
    case 192:
        dpi=2;
        QMessageBox::warning(this,"警告","当前显示比例为200%,某些图标可能识别不准确,建议调至(100%或125%)!\n详情请查看帮助或帮助文档!");
        break;
    default:
        showErrorWin("程序不支持当前显示比例,建议调至(100%或125%)!\n详情请查看帮助或帮助文档!");
        View_Deinit();
        break;
    }
}

//更新挑战次数/樱饼数量的QLineEdit显示
void MainWindow::updateInfo(int mode,int info)
{
    if(mode==TIMES_TYPE)
    {
        ui->editChallengetimes->setText(QString::number(info));
    }
    else if(mode==PROPS_TYPE)
    {
        ui->editPropCount->setText(QString::number(info));
    }
}
