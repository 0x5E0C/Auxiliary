#include "update.h"
#include "ui_update.h"
#include "qzipreader_p.h"

update::update(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::update)
{
    ui->setupUi(this);
    connect(ui->button_startupdate,SIGNAL(clicked()),this,SLOT(getDownloadAddr()));
    connect(ui->button_cancel,SIGNAL(clicked()),this,SLOT(cancelUpdate()));
}

update::~update()
{
    delete ui;
}

void update::showUpdateWindow()
{
    setWindowTitle("发现新版本");
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::Widget);
    setFixedSize(this->width(),this->height());
    show();
}

void update::getLastReleaseVersion()
{
    update_flag=true;
    QDir *downloaddir=new QDir(downloadpath+"/Auxiliary/");
    if(downloaddir->exists())
    {
        downloaddir->setPath(downloadpath+"/Auxiliary/");
        downloaddir->removeRecursively();
    }
    downloaddir->mkpath(downloadpath+"/Auxiliary/");
    QNetworkAccessManager *manager=new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setUrl(QUrl("https://gitee.com/api/v5/repos/wwx012138/Auxiliary/releases/latest"));
    reply=manager->get(request);
    connect(reply,SIGNAL(finished()),this,SLOT(saveVersionInfo()));
}

void update::saveVersionInfo()
{
    QByteArray content=reply->readAll();
    if(content.isEmpty())
    {
        QMessageBox::critical(this,"错误","网络未连接，无法检测更新！");
        return;
    }
    QJsonParseError jsonError;
    QJsonDocument jsonDoucment=QJsonDocument::fromJson(content,&jsonError);
    if(jsonError.error==QJsonParseError::NoError)
    {
        QJsonObject obj=jsonDoucment.object();
        lastversion=obj.value("tag_name").toString();
        disconnect(reply,SIGNAL(finished()),this,SLOT(saveVersionInfo()));
        if(lastversion!=version)
        {
            QString pattern("browser_download_url\":\"(.*)\"");
            QRegExp regexp(pattern);
            regexp.setMinimal(true);
            downloadurl=QString(content);
            if(downloadurl.contains(regexp))
            {
                regexp.capturedTexts();
                downloadurl=regexp.cap(1);
            }
            emit hasNewVersion();
        }
    }
}

void update::getDownloadAddr()
{
    if(downloadurl.isEmpty())
    {
        return;
    }
    QNetworkAccessManager *manager=new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setUrl(QUrl(downloadurl));
    reply=manager->get(request);
    connect(reply,SIGNAL(finished()),this,SLOT(getLastRelease()));
}

void update::getLastRelease()
{
    QString downloadaddr;
    downloadaddr=QString(reply->readAll());
    QString pattern("<a href=\"(.*)\">redirected");
    QRegExp regexp(pattern);
    regexp.setMinimal(true);
    if(downloadaddr.contains(regexp))
    {
        regexp.capturedTexts();
        downloadaddr=regexp.cap(1).remove(QRegExp("amp;"));
    }
    QNetworkAccessManager *manager=new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setUrl(QUrl(downloadaddr));
    reply=manager->get(request);
    QDir *downloaddir=new QDir(downloadpath+"/Auxiliary/"+lastversion);
    downloaddir->mkpath(downloadpath+"/Auxiliary/"+lastversion);
    downloadfile=new QFile(downloadpath+"/Auxiliary/"+lastversion+"/release.zip");
    if(!downloadfile->open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QMessageBox::critical(this,"错误","磁盘无法写入");
        return;
    }
    ui->tiplabel->setText("下载进度:");
    disconnect(reply,SIGNAL(finished()),this,SLOT(getLastRelease()));
    connect(reply,SIGNAL(readyRead()),this,SLOT(saveAsCache()));
    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(showProgress(qint64,qint64)));
    connect(reply,SIGNAL(finished()),this,SLOT(reinstallProgram()));
}

void update::saveAsCache()
{
    downloadfile->write(reply->readAll());
}

void update::showProgress(qint64 recbytes,qint64 totalbytes)
{
    ui->downloadprogress->setMaximum(totalbytes);
    ui->downloadprogress->setValue(recbytes);
    float rec=recbytes/1024.0/1024.0;
    float total=totalbytes/1024.0/1024.0;
    ui->downloadlabel->setText("("+QString::number(rec,'f',2)+"M/"+QString::number(total,'f',2)+"M"+")");
}

void update::reinstallProgram()
{
	downloadfile->close();
    if(update_flag)
    {
        clearUnzipDir();
        upzipProgram();
        renameOldProgram();
        copyProgram();
        clearDownloadCache();
        restartProgram();
    }
    else
    {
        QDir dir;
        dir.setPath(downloadpath+"/Auxiliary/");
        dir.removeRecursively();
        this->close();
    }
}

void update::upzipProgram()
{
    QZipReader zip(downloadpath+"/Auxiliary/"+lastversion+"/release.zip");
    zip.extractAll(downloadpath+"/Auxiliary/"+lastversion);
}

void update::clearUnzipDir()
{
    QDir *oldfile=new QDir(downloadpath+"/Auxiliary/"+lastversion);
    int filecount=oldfile->entryList().size();
    if(filecount!=3)
    {
        for(int i=0;i<filecount;i++)
        {
            if(oldfile->entryList().at(i)!="." && oldfile->entryList().at(i)!="..")
            {
                if(oldfile->entryList().at(i)!="release.zip")
                {
                    oldfile->remove(oldfile->entryList().at(i));
                }
            }
        }
    }
}

void update::clearOldFiles()
{
    QDir *oldfile=new QDir(QCoreApplication::applicationDirPath());
    int filecount=oldfile->entryList().size();
    for(int i=0;i<filecount;i++)
    {
        if(oldfile->entryList().at(i)!="." && oldfile->entryList().at(i)!="..")
        {
            if(oldfile->entryList().at(i).contains(".old"))
            {
                if(!oldfile->remove(oldfile->entryList().at(i)))
                {
                    QDir dir;
                    dir.setPath(QCoreApplication::applicationDirPath()+"/"+oldfile->entryList().at(i));
                    dir.removeRecursively();
                }
            }
        }
    }
}

void update::renameOldProgram()
{
    QDir *oldfile=new QDir(QCoreApplication::applicationDirPath());
    int filecount=oldfile->entryList().size();
    for(int i=0;i<filecount;i++)
    {
        if(oldfile->entryList().at(i)!="." && oldfile->entryList().at(i)!="..")
        {
            oldfile->rename(oldfile->entryList().at(i),oldfile->entryList().at(i)+".old");
        }
    }
}

void update::copyProgram()
{
    QString srcpath=downloadpath+"/Auxiliary/"+lastversion;
    QString dstpath=QCoreApplication::applicationDirPath();
    QDir *srcfile=new QDir(srcpath);
    int filecount=srcfile->entryList().size();
    for(int i=0;i<filecount;i++)
    {
        if(srcfile->entryList().at(i)!="." && srcfile->entryList().at(i)!=".." && srcfile->entryList().at(i)!="release.zip")
        {
            QFile::copy(srcpath+"/"+srcfile->entryList().at(i),dstpath+"/"+srcfile->entryList().at(i));
        }
    }
}

void update::clearDownloadCache()
{
    QDir dir;
    dir.setPath(downloadpath+"/Auxiliary/"+lastversion);
    dir.removeRecursively();
}

void update::restartProgram()
{
    QProcess *restartprocess=new QProcess(this);
    QString programpath=QApplication::applicationFilePath();
    restartprocess->startDetached(programpath);
    this->close();
    emit finished();
}

void update::cancelUpdate()
{
    update_flag=false;
    if(reply!=NULL)
    {
        reply->abort();
    }
}
