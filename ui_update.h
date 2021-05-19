/********************************************************************************
** Form generated from reading UI file 'update.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATE_H
#define UI_UPDATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_update
{
public:
    QProgressBar *downloadprogress;
    QLabel *tiplabel;
    QLabel *downloadlabel;
    QPushButton *button_cancel;
    QPushButton *button_startupdate;

    void setupUi(QWidget *update)
    {
        if (update->objectName().isEmpty())
            update->setObjectName(QString::fromUtf8("update"));
        update->resize(366, 142);
        downloadprogress = new QProgressBar(update);
        downloadprogress->setObjectName(QString::fromUtf8("downloadprogress"));
        downloadprogress->setGeometry(QRect(107, 30, 161, 23));
        downloadprogress->setValue(0);
        tiplabel = new QLabel(update);
        tiplabel->setObjectName(QString::fromUtf8("tiplabel"));
        tiplabel->setGeometry(QRect(30, 30, 71, 21));
        downloadlabel = new QLabel(update);
        downloadlabel->setObjectName(QString::fromUtf8("downloadlabel"));
        downloadlabel->setGeometry(QRect(270, 30, 131, 21));
        button_cancel = new QPushButton(update);
        button_cancel->setObjectName(QString::fromUtf8("button_cancel"));
        button_cancel->setGeometry(QRect(200, 80, 93, 28));
        button_startupdate = new QPushButton(update);
        button_startupdate->setObjectName(QString::fromUtf8("button_startupdate"));
        button_startupdate->setGeometry(QRect(60, 80, 93, 28));

        retranslateUi(update);

        QMetaObject::connectSlotsByName(update);
    } // setupUi

    void retranslateUi(QWidget *update)
    {
        update->setWindowTitle(QCoreApplication::translate("update", "Form", nullptr));
        tiplabel->setText(QCoreApplication::translate("update", "\344\270\213\350\275\275\350\277\233\345\272\246:", nullptr));
        downloadlabel->setText(QCoreApplication::translate("update", "(0/0M)", nullptr));
        button_cancel->setText(QCoreApplication::translate("update", "\345\217\226\346\266\210", nullptr));
        button_startupdate->setText(QCoreApplication::translate("update", "\345\274\200\345\247\213\346\233\264\346\226\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class update: public Ui_update {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATE_H
