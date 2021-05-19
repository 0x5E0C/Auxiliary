#include "setting.h"
#include "ui_setting.h"

setting::setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setting)
{
    ui->setupUi(this);
    setWindowFlags(0);
    setFixedSize(this->width(),this->height());
    viewInit();
    widgetsinfo.resize(index_end);
    connect(ui->check_stopWhenLimit,SIGNAL(stateChanged(int)),this,SLOT(changeEditLimitEnable(int)));
    connect(ui->button_ok,SIGNAL(clicked()),this,SLOT(getWidgetsInfo()));
    connect(ui->button_exit,SIGNAL(clicked()),this,SLOT(close()));
}

setting::~setting()
{
    delete ui;
}

/*函数功能:改变结界突破券相关ui的显示*/
void setting::changeEditLimitEnable(int state)
{
    if(state==Qt::Checked)
    {
        ui->label_jiejiePropCount->setEnabled(true);
        ui->edit_jiejiePropCount->setEnabled(true);
    }
    else if(state==Qt::Unchecked)
    {
        ui->label_jiejiePropCount->setEnabled(false);
        ui->edit_jiejiePropCount->setEnabled(false);
    }
}

/*函数功能:检查设置界面填入参数是否填写有误*/
bool setting::check()
{
    if(ui->edit_jiejiePropCount->isEnabled())
    {
        int propscount=ui->edit_jiejiePropCount->text().toInt();
        if(propscount<0 || propscount>30 || ui->edit_jiejiePropCount->text().isEmpty())
        {
            QMessageBox::critical(this,"错误","结界突破券数量输入错误!");
            return false;
        }
    }
    return true;
}

/*函数功能:获取当前界面的参数*/
void setting::getWidgetsInfo()
{
    if(!check())
    {
        return;
    }
    widgetsinfo[index_resolution]=(ui->resolution1->isChecked()==true)?1:2;
    widgetsinfo[index_magatama30]=ui->check_magatama30->checkState();
    widgetsinfo[index_strength30]=ui->check_strength30->checkState();
    widgetsinfo[index_gold2w]=ui->check_gold2w->checkState();
    widgetsinfo[index_gold3w]=ui->check_gold3w->checkState();
    widgetsinfo[index_autoprepare]=ui->check_autoPrepare->checkState();
    widgetsinfo[index_otheroperations]=ui->check_addOtherOperations->checkState();
    widgetsinfo[index_failstop]=ui->check_stopWhenFail->checkState();
    widgetsinfo[index_stopwhenlimit]=ui->check_stopWhenLimit->checkState();
    widgetsinfo[index_jiejiepropcount]=ui->edit_jiejiePropCount->text().toInt();
    widgetsinfo[index_popupwhenstop]=ui->check_popupWhenStop->checkState();
    widgetsinfo[index_updateflag]=ui->check_autoUpdate->checkState();
    saveSettingInfo();
    this->close();
    emit destroywindows(widgetsinfo);
}

/*函数功能:界面初始化*/
void setting::viewInit()
{
    if(ui->check_stopWhenLimit->checkState()==Qt::Checked)
    {
        ui->label_jiejiePropCount->setEnabled(true);
        ui->edit_jiejiePropCount->setEnabled(true);
    }
    else if(ui->check_stopWhenLimit->checkState()==Qt::Unchecked)
    {
        ui->label_jiejiePropCount->setEnabled(false);
        ui->edit_jiejiePropCount->setEnabled(false);
    }
}

/*函数功能:设置上一次保存的界面的选择*/
void setting::setArgs()
{
    if(widgetsinfo[index_resolution]==1)
    {
        ui->resolution1->setChecked(true);
    }
    else if(widgetsinfo[index_resolution]==2)
    {
        ui->resolution2->setChecked(true);
    }
    ui->check_magatama30->setChecked(widgetsinfo[index_magatama30]);
    ui->check_strength30->setChecked(widgetsinfo[index_strength30]);
    ui->check_gold2w->setChecked(widgetsinfo[index_gold2w]);
    ui->check_gold3w->setChecked(widgetsinfo[index_gold3w]);
    ui->check_autoPrepare->setChecked(widgetsinfo[index_autoprepare]);
    ui->check_addOtherOperations->setChecked(widgetsinfo[index_otheroperations]);
    ui->check_stopWhenFail->setChecked(widgetsinfo[index_failstop]);
    ui->check_stopWhenLimit->setChecked(widgetsinfo[index_stopwhenlimit]);
    ui->edit_jiejiePropCount->setText(QString::number(widgetsinfo[index_jiejiepropcount]));
    ui->check_popupWhenStop->setChecked(widgetsinfo[index_popupwhenstop]);
    ui->check_autoUpdate->setChecked(widgetsinfo[index_updateflag]);
    viewInit();
    emit destroywindows(widgetsinfo);
}

/*函数功能:保存本次设置*/
void setting::saveSettingInfo()
{
    QString currentpath=QDir::currentPath();
    QFile file(currentpath+"/config.ini");
    QString writedata;
    uint checkdata=0;
    if(file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        for(int i=0;i<index_end;i++)
        {
            writedata+=QString::number(widgetsinfo[i])+'\n';
            checkdata+=widgetsinfo[i];
        }
        writedata+=QString::number(checkdata);
        file.write(writedata.toLocal8Bit());
    }
    file.close();
}

/*函数功能:读取上一次界面参数*/
void setting::loadSettingInfo()
{
    QString currentpath=QDir::currentPath();
    QFile file(currentpath+"/config.ini");
    uint checkdata=0;
    updatewindow->clearOldFiles();
    if(file.exists() && file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        for(int i=0;i<index_end;i++)
        {
            widgetsinfo[i]=file.readLine().toUInt();
            checkdata+=widgetsinfo[i];
        }
        if(widgetsinfo[index_updateflag]==Qt::Checked)
        {
            connect(updatewindow,SIGNAL(finished()),this,SLOT(sendRestartProgramSignal()));
            updatewindow->showUpdateWindow();
        }
        if(file.readLine().toUInt()==checkdata)
        {
            setArgs();
        }
    }
}

/*函数功能:冻结设置界面*/
void setting::freezeUI()
{
    ui->resolution1->setEnabled(false);
    ui->resolution2->setEnabled(false);
    ui->check_magatama30->setEnabled(false);
    ui->check_strength30->setEnabled(false);
    ui->check_gold2w->setEnabled(false);
    ui->check_gold3w->setEnabled(false);
    ui->check_autoPrepare->setEnabled(false);
    ui->check_addOtherOperations->setEnabled(false);
    ui->check_stopWhenFail->setEnabled(false);
    ui->check_stopWhenLimit->setEnabled(false);
    ui->check_popupWhenStop->setEnabled(false);
    ui->edit_jiejiePropCount->setEnabled(false);
}

/*函数功能:解冻设置界面*/
void setting::unfreezeUI()
{
    ui->resolution1->setEnabled(true);
    ui->resolution2->setEnabled(true);
    ui->check_magatama30->setEnabled(true);
    ui->check_strength30->setEnabled(true);
    ui->check_gold2w->setEnabled(true);
    ui->check_gold3w->setEnabled(true);
    ui->check_autoPrepare->setEnabled(true);
    ui->check_addOtherOperations->setEnabled(true);
    ui->check_stopWhenFail->setEnabled(true);
    ui->check_stopWhenLimit->setEnabled(true);
    ui->check_popupWhenStop->setEnabled(true);
    ui->edit_jiejiePropCount->setEnabled(true);
    viewInit();
}

void setting::sendRestartProgramSignal()
{
    emit restart();
}
