#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    hotkeymanager->setHook();
    setWindowFlags(Qt::Widget);
    setFixedSize(this->width(),this->height());
    setWindowTitle("辅助器");
    viewInit();
    getAppDPI();
    connect(ui->yuhun_chooseFloor,SIGNAL(currentIndexChanged(int)),this,SLOT(changeChallengeMode(int)));
    connect(ui->yuhun_isTeamMode,SIGNAL(stateChanged(int)),this,SLOT(changeTeamMode(int)));
    connect(ui->yuhun_button_start,SIGNAL(clicked()),this,SLOT(start()));
    connect(ui->yuhun_button_pause,SIGNAL(clicked()),this,SLOT(pause()));
    connect(ui->yuhun_button_stop,SIGNAL(clicked()),this,SLOT(stop()));
    connect(ui->juexing_isTeamMode,SIGNAL(stateChanged(int)),this,SLOT(changeTeamMode(int)));
    connect(ui->juexing_button_start,SIGNAL(clicked()),this,SLOT(start()));
    connect(ui->juexing_button_pause,SIGNAL(clicked()),this,SLOT(pause()));
    connect(ui->juexing_button_stop,SIGNAL(clicked()),this,SLOT(stop()));
    connect(ui->yuling_button_start,SIGNAL(clicked()),this,SLOT(start()));
    connect(ui->yuling_button_pause,SIGNAL(clicked()),this,SLOT(pause()));
    connect(ui->yuling_button_stop,SIGNAL(clicked()),this,SLOT(stop()));
    connect(ui->button_open_setting,SIGNAL(clicked()),this,SLOT(openSettingPage()));
    connect(settingwindow,SIGNAL(destroywindows(QVector<quint8>)),this,SLOT(getSettingInfo(QVector<quint8>)));
    connect(settingwindow,SIGNAL(restart()),this,SLOT(close()));
    connect(hotkeymanager,SIGNAL(hotkeyevent()),this,SLOT(pause()));
    connect(promptmanager,SIGNAL(errorevent()),this,SLOT(stop()));
    connect(promptmanager,SIGNAL(updateShowArea(QString,int)),this,SLOT(addToShowArea(QString,int)));
    connect(promptmanager,SIGNAL(finishevent()),this,SLOT(stop()));
    connect(promptmanager,SIGNAL(updateUI(int,int,int)),this,SLOT(updateInfo(int,int,int)));
    connect(promptmanager,SIGNAL(failevent()),this,SLOT(stop()));
    settingwindow->loadSettingInfo();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*函数功能:开启识别功能*/
void MainWindow::start()
{
    if(check())
    {
        startflag=true;
        getWidgetsInfo();
        freezeUI();
        settingwindow->freezeUI();
        addToShowArea("即将开始!",INFO);
        addToShowArea("读取设置中...",INFO);
        addToShowArea("已选择副本："+guiInfo.floortext,INFO);
        classifymanager=new classify();
        classifymanager->startTask();

    }
}

/*函数功能:暂停识别，不使能ui，防止误操作*/
void MainWindow::pause()
{
    startflag=false;
    settingwindow->unfreezeUI();
    if(freezeflag==C_YUHUN)
    {
        ui->yuhun_button_start->setEnabled(true);
    }
    else if(freezeflag==C_JUEXING)
    {
        ui->juexing_button_start->setEnabled(true);
    }
    else if(freezeflag==C_YULING)
    {
        ui->yuling_button_start->setEnabled(true);
    }
    for(int i=0;i<process_count;i++)
    {
        *threadflaglist[i]=false;
    }
    addToShowArea("已暂停!",INFO);
}

/*函数功能:停止识别，使能ui*/
void MainWindow::stop()
{
    if(startflag)
    {
        if(guiInfo.popupstop)
        {
            QMessageBox::information(this,"提示","程序已停止!");
        }
    }
    startflag=false;
    unfreezeUI();
    settingwindow->unfreezeUI();
    for(int i=0;i<process_count;i++)
    {
        *threadflaglist[i]=false;
    }
}

/*函数功能:根据选择的层数改变ui*/
void MainWindow::changeChallengeMode(int floor)
{
    if(floor==not_choose)
    {
        setTeamModeEnbale(C_YUHUN,false);
        ui->yuhun_label_propcount->setEnabled(false);
        ui->yuhun_editPropCount->setEnabled(false);
        ui->yuhun_label_challengetimes->setEnabled(false);
        ui->yuhun_editChallengetimes->setEnabled(false);
    }
    else if(floor==floor_1_10 || floor==floor_11 || floor==floor_rlzy1 || floor==floor_rlzy2 || floor==floor_rlzy3)
    {
        setTeamModeEnbale(C_YUHUN,true);
        ui->yuhun_label_propcount->setEnabled(true);
        ui->yuhun_editPropCount->setEnabled(true);
        ui->yuhun_label_challengetimes->setEnabled(false);
        ui->yuhun_editChallengetimes->setEnabled(false);
    }
    else if(floor==floor_tan || floor==floor_chen || floor==floor_chi)
    {
        setTeamModeEnbale(C_YUHUN,false);
        ui->yuhun_label_propcount->setEnabled(false);
        ui->yuhun_editPropCount->setEnabled(false);
        ui->yuhun_label_challengetimes->setEnabled(true);
        ui->yuhun_editChallengetimes->setEnabled(true);
    }
}

/*函数功能:根据是否选择组队模式改变ui*/
void MainWindow::changeTeamMode(int state)
{
    if(ui->pages->currentIndex()==C_YUHUN)
    {
        if(state==Qt::Checked)
        {
            ui->yuhun_label_personcount->setEnabled(true);
            ui->yuhun_editPersonCount->setEnabled(true);
        }
        else if(state==Qt::Unchecked)
        {
            ui->yuhun_label_personcount->setEnabled(false);
            ui->yuhun_editPersonCount->setEnabled(false);
        }
    }
    else if(ui->pages->currentIndex()==C_JUEXING)
    {
        if(state==Qt::Checked)
        {
            ui->juexing_label_personcount->setEnabled(true);
            ui->juexing_editPersonCount->setEnabled(true);
        }
        else if(state==Qt::Unchecked)
        {
            ui->juexing_label_personcount->setEnabled(false);
            ui->juexing_editPersonCount->setEnabled(false);
        }
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
bool MainWindow::check()
{
    if(ui->pages->currentIndex()==C_YUHUN)
    {
        int person_count,prop_count,challengetimes,floor;
        person_count=ui->yuhun_editPersonCount->text().toInt();
        prop_count=ui->yuhun_editPropCount->text().toInt();
        challengetimes=ui->yuhun_editChallengetimes->text().toInt();
        floor=ui->yuhun_chooseFloor->currentIndex();
        if(ui->yuhun_chooseFloor->currentIndex()==not_choose)
        {
            QMessageBox::critical(this,"错误","未选择副本!");
            addToShowArea("错误：未选择副本!",ERR);
            return false;
        }
        else
        {
            if(ui->yuhun_editPersonCount->isEnabled() && ui->yuhun_isTeamMode->checkState()==Qt::Checked && (person_count>3 || person_count<=1))
            {
                QMessageBox::critical(this,"错误","组队人数输入错误!");
                addToShowArea("错误：组队人数输入应在1~3范围内!",ERR);
                return false;
            }
            if((floor==floor_1_10 || floor==floor_11 || floor==floor_rlzy1 || floor==floor_rlzy2 || floor==floor_rlzy3) && ui->yuhun_editPropCount->isEnabled() && prop_count<=0)
            {
                QMessageBox::critical(this,"错误","樱饼数量输入错误!");
                addToShowArea("错误：樱饼数量输入应大于0!",ERR);
                return false;
            }
            if((floor==floor_tan || floor==floor_chen || floor==floor_chi) && ui->yuhun_editChallengetimes->isEnabled() && challengetimes<=0)
            {
                QMessageBox::critical(this,"错误","挑战次数输入错误!");
                addToShowArea("错误：挑战次数输入应大于0!",ERR);
                return false;
            }
        }
    }
    else if(ui->pages->currentIndex()==C_JUEXING)
    {
        int person_count,prop_count;
        person_count=ui->juexing_editPersonCount->text().toInt();
        prop_count=ui->juexing_editPropCount->text().toInt();
        if(ui->juexing_isTeamMode->isEnabled() && ui->juexing_isTeamMode->checkState()==Qt::Checked && (person_count>3 || person_count<=1))
        {
            QMessageBox::critical(this,"错误","组队人数输入错误!");
            addToShowArea("错误：组队人数输入应在1~3范围内!",ERR);
            return false;
        }
        if(prop_count<=0)
        {
            QMessageBox::critical(this,"错误","樱饼数量输入错误!");
            addToShowArea("错误：樱饼数量输入应大于0!",ERR);
            return false;
        }
    }
    else if(ui->pages->currentIndex()==C_YULING)
    {
        int challengetimes;
        challengetimes=ui->yuling_editChallengetimes->text().toInt();
        if(challengetimes<=0)
        {
            QMessageBox::critical(this,"错误","挑战次数输入错误!");
            addToShowArea("错误：挑战次数输入应大于0!",ERR);
            return false;
        }
    }
    return true;
}

/*函数功能:获得当前时间，用于提示信息*/
QString MainWindow::getCurrenttime(QString pattern)
{
    QDateTime currenttime;
    currenttime= QDateTime::currentDateTime();
    return currenttime.toString(pattern);
}

/*函数功能:初始化ui显示*/
void MainWindow::viewInit()
{
    ui->yuhun_isTeamMode->setEnabled(false);
    ui->yuhun_label_personcount->setEnabled(false);
    ui->yuhun_editPersonCount->setEnabled(false);
    ui->yuhun_label_propcount->setEnabled(false);
    ui->yuhun_editPropCount->setEnabled(false);
    ui->yuhun_label_challengetimes->setEnabled(false);
    ui->yuhun_editChallengetimes->setEnabled(false);
    ui->juexing_label_personcount->setEnabled(false);
    ui->juexing_editPersonCount->setEnabled(false);
}

/*函数功能:控制所有widget的状态*/
void MainWindow::setAllWidgets(bool state)
{
    ui->yuhun_chooseFloor->setEnabled(state);
    ui->yuhun_isTeamMode->setEnabled(state);
    ui->yuhun_editPersonCount->setEnabled(state);
    ui->yuhun_editPropCount->setEnabled(state);
    ui->yuhun_editChallengetimes->setEnabled(state);
    ui->yuhun_button_start->setEnabled(state);
    ui->yuhun_button_pause->setEnabled(state);
    ui->yuhun_button_stop->setEnabled(state);
    ui->juexing_isTeamMode->setEnabled(state);
    ui->juexing_editPersonCount->setEnabled(state);
    ui->juexing_editPropCount->setEnabled(state);
    ui->juexing_button_start->setEnabled(state);
    ui->juexing_button_pause->setEnabled(state);
    ui->juexing_button_stop->setEnabled(state);
    ui->yuling_editChallengetimes->setEnabled(state);
    ui->yuling_button_start->setEnabled(state);
    ui->yuling_button_pause->setEnabled(state);
    ui->yuling_button_stop->setEnabled(state);
}

/*函数功能:控制组队相关ui*/
void MainWindow::setTeamModeEnbale(int pages,bool state)
{
    if(state)
    {
        if(pages==C_YUHUN)
        {
            ui->yuhun_isTeamMode->setEnabled(true);
            if(ui->yuhun_isTeamMode->checkState()==Qt::Checked)
            {
                ui->yuhun_label_personcount->setEnabled(true);
                ui->yuhun_editPersonCount->setEnabled(true);
            }
            else if(ui->yuhun_isTeamMode->checkState()==Qt::Unchecked)
            {
                ui->yuhun_label_personcount->setEnabled(false);
                ui->yuhun_editPersonCount->setEnabled(false);
            }
        }
        else if(pages==C_JUEXING)
        {
            ui->juexing_isTeamMode->setEnabled(true);
            if(ui->juexing_isTeamMode->checkState()==Qt::Checked)
            {
                ui->juexing_label_personcount->setEnabled(true);
                ui->juexing_editPersonCount->setEnabled(true);
            }
            else if(ui->juexing_isTeamMode->checkState()==Qt::Unchecked)
            {
                ui->juexing_label_personcount->setEnabled(false);
                ui->juexing_editPersonCount->setEnabled(false);
            }
        }
    }
    else
    {
        if(pages==C_YUHUN)
        {
            ui->yuhun_isTeamMode->setEnabled(false);
            ui->yuhun_label_personcount->setEnabled(false);
            ui->yuhun_editPersonCount->setEnabled(false);
        }
        else if(pages==C_JUEXING)
        {
            ui->juexing_isTeamMode->setEnabled(false);
            ui->juexing_label_personcount->setEnabled(false);
            ui->juexing_editPersonCount->setEnabled(false);
        }
    }
}

/*函数功能:获取所有ui交互信息*/
void MainWindow::getWidgetsInfo()
{
    guiInfo.challengetype=ui->pages->currentIndex();
    if(ui->pages->currentIndex()==C_YUHUN)
    {
        guiInfo.mfloor=ui->yuhun_chooseFloor->currentIndex();
        if(ui->yuhun_isTeamMode->isChecked() && ui->yuhun_isTeamMode->isEnabled())
        {
            guiInfo.isteam=true;
            guiInfo.person=ui->yuhun_editPersonCount->text().toInt();
        }
        else
        {
            guiInfo.isteam=false;
            guiInfo.person=-1;
        }
        if(ui->yuhun_editPropCount->isEnabled())
        {
            guiInfo.propcount=ui->yuhun_editPropCount->text().toInt();
        }
        else
        {
            guiInfo.propcount=-1;
        }
        if(ui->yuhun_editChallengetimes->isEnabled())
        {
            guiInfo.challengetimes=ui->yuhun_editChallengetimes->text().toInt();
        }
        else
        {
            guiInfo.challengetimes=-1;
        }
        guiInfo.floortext=ui->yuhun_chooseFloor->currentText();
    }
    else if(ui->pages->currentIndex()==C_JUEXING)
    {
        if(ui->juexing_isTeamMode->isChecked() && ui->juexing_isTeamMode->isEnabled())
        {
            guiInfo.isteam=true;
            guiInfo.person=ui->juexing_editPersonCount->text().toInt();
        }
        else
        {
            guiInfo.isteam=false;
            guiInfo.person=-1;
        }
        if(ui->juexing_editPropCount->isEnabled())
        {
            guiInfo.propcount=ui->juexing_editPropCount->text().toInt();
        }
        else
        {
            guiInfo.propcount=-1;
        }
        guiInfo.floortext="觉醒";
    }
    else if(ui->pages->currentIndex()==C_YULING)
    {
        if(ui->yuling_editChallengetimes->isEnabled())
        {
            guiInfo.challengetimes=ui->yuling_editChallengetimes->text().toInt();
        }
        else
        {
            guiInfo.challengetimes=-1;
        }
        guiInfo.isteam=false;
        guiInfo.floortext="御灵";
    }
}

/*函数功能:获取系统dpi*/
void MainWindow::getAppDPI()
{
#ifdef USE_MINGW32
	HDC appDc = GetDC(FindWindowEx(NULL, NULL, NULL, title.toLocal8Bit()));
#elif USE_MSVC
	HDC appDc = GetDC(FindWindowEx(NULL, NULL, NULL, title.toStdWString().c_str()));
#endif
    int verticalDPI = GetDeviceCaps(appDc,LOGPIXELSY);
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
        setAllWidgets(false);
        break;
    }
}

/*函数功能:更新挑战次数/樱饼数量的QLineEdit显示*/
void MainWindow::updateInfo(int mode,int info,int flag)
{
    if(mode==TIMES_TYPE)
    {
        if(flag==C_YUHUN)
        {
            ui->yuhun_editChallengetimes->setText(QString::number(info));
        }
        else if(flag==C_YULING)
        {
            ui->yuling_editChallengetimes->setText(QString::number(info));
        }
    }
    else if(mode==PROPS_TYPE)
    {
        if(flag==C_YUHUN)
        {
            ui->yuhun_editPropCount->setText(QString::number(info));
        }
        else if(flag==C_JUEXING)
        {
            ui->juexing_editPropCount->setText(QString::number(info));
        }
    }
}

/*函数功能:打开设置界面*/
void MainWindow::openSettingPage()
{
    settingwindow->setWindowTitle("设置");
    settingwindow->show();
}

/*函数功能:获取设置界面参数*/
void MainWindow::getSettingInfo(QVector<quint8> infolist)
{
    if(infolist[index_resolution]==1)
    {
        guiInfo.resolution="1440849";
        guiInfo.winheight=849;
    }
    else if(infolist[index_resolution]==2)
    {
        guiInfo.resolution="961579";
        guiInfo.winheight=579;
    }
    guiInfo.magatama30=infolist[index_magatama30];
    guiInfo.strength30=infolist[index_strength30];
    guiInfo.gold2w=infolist[index_gold2w];
    guiInfo.gold3w=infolist[index_gold3w];
    guiInfo.autoprepare=infolist[index_autoprepare];
    guiInfo.addoperations=infolist[index_otheroperations];
    guiInfo.failstop=infolist[index_failstop];
    guiInfo.stopwhenlimit=infolist[index_stopwhenlimit];
    guiInfo.jiejiepropcount=infolist[index_jiejiepropcount];
    guiInfo.popupstop=infolist[index_popupwhenstop];
}

/*函数功能:冻结部分UI*/
void MainWindow::freezeUI()
{
    setAllWidgets(false);
    switch(ui->pages->currentIndex())
    {
    case C_YUHUN:
        freezeflag=C_YUHUN;
        ui->yuhun_button_pause->setEnabled(true);
        ui->yuhun_button_stop->setEnabled(true);
        break;
    case C_JUEXING:
        freezeflag=C_JUEXING;
        ui->juexing_button_pause->setEnabled(true);
        ui->juexing_button_stop->setEnabled(true);
        break;
    case C_YULING:
        freezeflag=C_YULING;
        ui->yuling_button_pause->setEnabled(true);
        ui->yuling_button_stop->setEnabled(true);
        break;
    default:
        break;
    }
}

/*函数功能:解冻部分UI*/
void MainWindow::unfreezeUI()
{
    setAllWidgets(true);
    changeChallengeMode(ui->yuhun_chooseFloor->currentIndex());
    setTeamModeEnbale(C_JUEXING,true);
}
