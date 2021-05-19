﻿#ifndef UPDATE_H
#define UPDATE_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QNetworkProxy>
#include <QProcess>
#include "config.h"

namespace Ui {
class update;
}

class update : public QWidget
{
    Q_OBJECT

signals:
    void finished();

public:
    explicit update(QWidget *parent = nullptr);
    ~update();
    void showUpdateWindow();
    void clearOldFiles();

private:
    Ui::update *ui;
    bool update_flag;
    QNetworkReply *reply=NULL;
    QString lastversion=NULL;
    QFile *downloadfile=NULL;
    void getDownloadAddr(QString url);
    void upzipProgram();
    void clearUnzipDir();
    void renameOldProgram();
    void copyProgram();
    void clearDownloadCache();
    void restartProgram();

private slots:
    void getLastReleaseVersion();
    void getLastRelease();
    void saveVersionInfo();
    void saveAsCache();
    void showProgress(qint64 recbytes,qint64 totalbytes);
    void reinstallProgram();
    void cancelUpdate();
};

#endif // UPDATE_H
