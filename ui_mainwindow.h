/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *pages;
    QWidget *yuhunpage;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *yuhun_label_personcount;
    QLineEdit *yuhun_editPropCount;
    QLineEdit *yuhun_editChallengetimes;
    QLineEdit *yuhun_editPersonCount;
    QCheckBox *yuhun_isTeamMode;
    QComboBox *yuhun_chooseFloor;
    QLabel *yuhun_label_challengetimes;
    QLabel *yuhun_label_propcount;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *yuhun_button_start;
    QPushButton *yuhun_button_pause;
    QPushButton *yuhun_button_stop;
    QWidget *juexingpage;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *juexing_button_start;
    QPushButton *juexing_button_pause;
    QPushButton *juexing_button_stop;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QLineEdit *juexing_editPersonCount;
    QLineEdit *juexing_editPropCount;
    QLabel *juexing_label_personcount;
    QCheckBox *juexing_isTeamMode;
    QLabel *juexing_label_propcount;
    QWidget *yulingpage;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_3;
    QLabel *yuling_label_challengetimes;
    QLineEdit *yuling_editChallengetimes;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QPushButton *yuling_button_start;
    QPushButton *yuling_button_pause;
    QPushButton *yuling_button_stop;
    QWidget *settingpage;
    QPushButton *button_open_setting;
    QTextBrowser *showInfoArea;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(500, 450);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pages = new QTabWidget(centralwidget);
        pages->setObjectName(QString::fromUtf8("pages"));
        pages->setGeometry(QRect(0, 0, 501, 301));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        pages->setFont(font);
        pages->setStyleSheet(QString::fromUtf8(""));
        yuhunpage = new QWidget();
        yuhunpage->setObjectName(QString::fromUtf8("yuhunpage"));
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(false);
        font1.setWeight(50);
        yuhunpage->setFont(font1);
        gridLayoutWidget = new QWidget(yuhunpage);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(40, 20, 251, 211));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        yuhun_label_personcount = new QLabel(gridLayoutWidget);
        yuhun_label_personcount->setObjectName(QString::fromUtf8("yuhun_label_personcount"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        yuhun_label_personcount->setFont(font2);

        gridLayout->addWidget(yuhun_label_personcount, 2, 0, 1, 1);

        yuhun_editPropCount = new QLineEdit(gridLayoutWidget);
        yuhun_editPropCount->setObjectName(QString::fromUtf8("yuhun_editPropCount"));

        gridLayout->addWidget(yuhun_editPropCount, 3, 1, 1, 1);

        yuhun_editChallengetimes = new QLineEdit(gridLayoutWidget);
        yuhun_editChallengetimes->setObjectName(QString::fromUtf8("yuhun_editChallengetimes"));

        gridLayout->addWidget(yuhun_editChallengetimes, 4, 1, 1, 1);

        yuhun_editPersonCount = new QLineEdit(gridLayoutWidget);
        yuhun_editPersonCount->setObjectName(QString::fromUtf8("yuhun_editPersonCount"));

        gridLayout->addWidget(yuhun_editPersonCount, 2, 1, 1, 1);

        yuhun_isTeamMode = new QCheckBox(gridLayoutWidget);
        yuhun_isTeamMode->setObjectName(QString::fromUtf8("yuhun_isTeamMode"));
        yuhun_isTeamMode->setFont(font2);

        gridLayout->addWidget(yuhun_isTeamMode, 1, 0, 1, 1);

        yuhun_chooseFloor = new QComboBox(gridLayoutWidget);
        yuhun_chooseFloor->addItem(QString());
        yuhun_chooseFloor->addItem(QString());
        yuhun_chooseFloor->addItem(QString());
        yuhun_chooseFloor->addItem(QString());
        yuhun_chooseFloor->addItem(QString());
        yuhun_chooseFloor->addItem(QString());
        yuhun_chooseFloor->addItem(QString());
        yuhun_chooseFloor->addItem(QString());
        yuhun_chooseFloor->addItem(QString());
        yuhun_chooseFloor->setObjectName(QString::fromUtf8("yuhun_chooseFloor"));
        yuhun_chooseFloor->setFont(font2);

        gridLayout->addWidget(yuhun_chooseFloor, 0, 0, 1, 1);

        yuhun_label_challengetimes = new QLabel(gridLayoutWidget);
        yuhun_label_challengetimes->setObjectName(QString::fromUtf8("yuhun_label_challengetimes"));
        yuhun_label_challengetimes->setFont(font2);

        gridLayout->addWidget(yuhun_label_challengetimes, 4, 0, 1, 1);

        yuhun_label_propcount = new QLabel(gridLayoutWidget);
        yuhun_label_propcount->setObjectName(QString::fromUtf8("yuhun_label_propcount"));
        yuhun_label_propcount->setFont(font2);

        gridLayout->addWidget(yuhun_label_propcount, 3, 0, 1, 1);

        verticalLayoutWidget = new QWidget(yuhunpage);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(330, 60, 119, 141));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        yuhun_button_start = new QPushButton(verticalLayoutWidget);
        yuhun_button_start->setObjectName(QString::fromUtf8("yuhun_button_start"));
        yuhun_button_start->setFont(font2);

        verticalLayout->addWidget(yuhun_button_start);

        yuhun_button_pause = new QPushButton(verticalLayoutWidget);
        yuhun_button_pause->setObjectName(QString::fromUtf8("yuhun_button_pause"));
        yuhun_button_pause->setFont(font2);

        verticalLayout->addWidget(yuhun_button_pause);

        yuhun_button_stop = new QPushButton(verticalLayoutWidget);
        yuhun_button_stop->setObjectName(QString::fromUtf8("yuhun_button_stop"));
        yuhun_button_stop->setFont(font2);

        verticalLayout->addWidget(yuhun_button_stop);

        pages->addTab(yuhunpage, QString());
        juexingpage = new QWidget();
        juexingpage->setObjectName(QString::fromUtf8("juexingpage"));
        verticalLayoutWidget_2 = new QWidget(juexingpage);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(330, 60, 119, 141));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        juexing_button_start = new QPushButton(verticalLayoutWidget_2);
        juexing_button_start->setObjectName(QString::fromUtf8("juexing_button_start"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font3.setPointSize(11);
        font3.setBold(false);
        font3.setWeight(50);
        juexing_button_start->setFont(font3);

        verticalLayout_2->addWidget(juexing_button_start);

        juexing_button_pause = new QPushButton(verticalLayoutWidget_2);
        juexing_button_pause->setObjectName(QString::fromUtf8("juexing_button_pause"));
        QFont font4;
        font4.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font4.setPointSize(11);
        juexing_button_pause->setFont(font4);

        verticalLayout_2->addWidget(juexing_button_pause);

        juexing_button_stop = new QPushButton(verticalLayoutWidget_2);
        juexing_button_stop->setObjectName(QString::fromUtf8("juexing_button_stop"));
        juexing_button_stop->setFont(font4);

        verticalLayout_2->addWidget(juexing_button_stop);

        gridLayoutWidget_2 = new QWidget(juexingpage);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(40, 70, 251, 121));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        juexing_editPersonCount = new QLineEdit(gridLayoutWidget_2);
        juexing_editPersonCount->setObjectName(QString::fromUtf8("juexing_editPersonCount"));
        juexing_editPersonCount->setMinimumSize(QSize(58, 0));
        juexing_editPersonCount->setMaximumSize(QSize(58, 16777215));

        gridLayout_2->addWidget(juexing_editPersonCount, 1, 1, 1, 1);

        juexing_editPropCount = new QLineEdit(gridLayoutWidget_2);
        juexing_editPropCount->setObjectName(QString::fromUtf8("juexing_editPropCount"));
        juexing_editPropCount->setMinimumSize(QSize(58, 0));
        juexing_editPropCount->setMaximumSize(QSize(58, 16777215));

        gridLayout_2->addWidget(juexing_editPropCount, 2, 1, 1, 1);

        juexing_label_personcount = new QLabel(gridLayoutWidget_2);
        juexing_label_personcount->setObjectName(QString::fromUtf8("juexing_label_personcount"));
        juexing_label_personcount->setFont(font4);

        gridLayout_2->addWidget(juexing_label_personcount, 1, 0, 1, 1);

        juexing_isTeamMode = new QCheckBox(gridLayoutWidget_2);
        juexing_isTeamMode->setObjectName(QString::fromUtf8("juexing_isTeamMode"));
        juexing_isTeamMode->setFont(font4);

        gridLayout_2->addWidget(juexing_isTeamMode, 0, 0, 1, 1);

        juexing_label_propcount = new QLabel(gridLayoutWidget_2);
        juexing_label_propcount->setObjectName(QString::fromUtf8("juexing_label_propcount"));
        juexing_label_propcount->setFont(font4);

        gridLayout_2->addWidget(juexing_label_propcount, 2, 0, 1, 1);

        pages->addTab(juexingpage, QString());
        yulingpage = new QWidget();
        yulingpage->setObjectName(QString::fromUtf8("yulingpage"));
        gridLayoutWidget_3 = new QWidget(yulingpage);
        gridLayoutWidget_3->setObjectName(QString::fromUtf8("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(60, 100, 181, 61));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        yuling_label_challengetimes = new QLabel(gridLayoutWidget_3);
        yuling_label_challengetimes->setObjectName(QString::fromUtf8("yuling_label_challengetimes"));
        yuling_label_challengetimes->setFont(font4);

        gridLayout_3->addWidget(yuling_label_challengetimes, 0, 0, 1, 1);

        yuling_editChallengetimes = new QLineEdit(gridLayoutWidget_3);
        yuling_editChallengetimes->setObjectName(QString::fromUtf8("yuling_editChallengetimes"));

        gridLayout_3->addWidget(yuling_editChallengetimes, 0, 1, 1, 1);

        verticalLayoutWidget_3 = new QWidget(yulingpage);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(330, 60, 119, 141));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        yuling_button_start = new QPushButton(verticalLayoutWidget_3);
        yuling_button_start->setObjectName(QString::fromUtf8("yuling_button_start"));
        yuling_button_start->setFont(font4);

        verticalLayout_3->addWidget(yuling_button_start);

        yuling_button_pause = new QPushButton(verticalLayoutWidget_3);
        yuling_button_pause->setObjectName(QString::fromUtf8("yuling_button_pause"));
        yuling_button_pause->setFont(font4);

        verticalLayout_3->addWidget(yuling_button_pause);

        yuling_button_stop = new QPushButton(verticalLayoutWidget_3);
        yuling_button_stop->setObjectName(QString::fromUtf8("yuling_button_stop"));
        yuling_button_stop->setFont(font4);

        verticalLayout_3->addWidget(yuling_button_stop);

        pages->addTab(yulingpage, QString());
        settingpage = new QWidget();
        settingpage->setObjectName(QString::fromUtf8("settingpage"));
        button_open_setting = new QPushButton(settingpage);
        button_open_setting->setObjectName(QString::fromUtf8("button_open_setting"));
        button_open_setting->setGeometry(QRect(50, 40, 141, 41));
        button_open_setting->setFont(font4);
        pages->addTab(settingpage, QString());
        showInfoArea = new QTextBrowser(centralwidget);
        showInfoArea->setObjectName(QString::fromUtf8("showInfoArea"));
        showInfoArea->setGeometry(QRect(0, 300, 500, 130));
        QFont font5;
        font5.setPointSize(11);
        showInfoArea->setFont(font5);
        showInfoArea->setStyleSheet(QString::fromUtf8("background-color:black;color:rgb(127,255,0)"));
        MainWindow->setCentralWidget(centralwidget);
        showInfoArea->raise();
        pages->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 500, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        pages->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        yuhun_label_personcount->setText(QCoreApplication::translate("MainWindow", "\344\272\272\346\225\260(\344\270\212\351\231\2203):", nullptr));
        yuhun_isTeamMode->setText(QCoreApplication::translate("MainWindow", "\347\273\204\351\230\237\346\250\241\345\274\217", nullptr));
        yuhun_chooseFloor->setItemText(0, QCoreApplication::translate("MainWindow", "\350\257\267\351\200\211\346\213\251\345\211\257\346\234\254\347\261\273\345\236\213", nullptr));
        yuhun_chooseFloor->setItemText(1, QCoreApplication::translate("MainWindow", "1~10\345\261\202", nullptr));
        yuhun_chooseFloor->setItemText(2, QCoreApplication::translate("MainWindow", "\346\202\262\351\270\243", nullptr));
        yuhun_chooseFloor->setItemText(3, QCoreApplication::translate("MainWindow", "\350\264\252", nullptr));
        yuhun_chooseFloor->setItemText(4, QCoreApplication::translate("MainWindow", "\345\227\224", nullptr));
        yuhun_chooseFloor->setItemText(5, QCoreApplication::translate("MainWindow", "\347\227\264", nullptr));
        yuhun_chooseFloor->setItemText(6, QCoreApplication::translate("MainWindow", "\346\227\245\350\275\256\344\271\213\345\237\216 1\345\261\202", nullptr));
        yuhun_chooseFloor->setItemText(7, QCoreApplication::translate("MainWindow", "\346\227\245\350\275\256\344\271\213\345\237\216 2\345\261\202", nullptr));
        yuhun_chooseFloor->setItemText(8, QCoreApplication::translate("MainWindow", "\346\227\245\350\275\256\344\271\213\345\237\216 3\345\261\202", nullptr));

        yuhun_chooseFloor->setCurrentText(QCoreApplication::translate("MainWindow", "\350\257\267\351\200\211\346\213\251\345\211\257\346\234\254\347\261\273\345\236\213", nullptr));
        yuhun_label_challengetimes->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256\346\214\221\346\210\230\346\254\241\346\225\260:", nullptr));
        yuhun_label_propcount->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256\346\250\261\351\245\274(\344\275\223\345\212\233)\346\225\260\351\207\217:", nullptr));
        yuhun_button_start->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        yuhun_button_pause->setText(QCoreApplication::translate("MainWindow", "\346\232\202\345\201\234", nullptr));
        yuhun_button_stop->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242", nullptr));
        pages->setTabText(pages->indexOf(yuhunpage), QCoreApplication::translate("MainWindow", "\345\276\241\351\255\202", nullptr));
        juexing_button_start->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        juexing_button_pause->setText(QCoreApplication::translate("MainWindow", "\346\232\202\345\201\234", nullptr));
        juexing_button_stop->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242", nullptr));
        juexing_label_personcount->setText(QCoreApplication::translate("MainWindow", "\344\272\272\346\225\260(\344\270\212\351\231\2203):", nullptr));
        juexing_isTeamMode->setText(QCoreApplication::translate("MainWindow", "\347\273\204\351\230\237\346\250\241\345\274\217", nullptr));
        juexing_label_propcount->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256\346\250\261\351\245\274(\344\275\223\345\212\233)\346\225\260\351\207\217:", nullptr));
        pages->setTabText(pages->indexOf(juexingpage), QCoreApplication::translate("MainWindow", "\350\247\211\351\206\222", nullptr));
        yuling_label_challengetimes->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256\346\214\221\346\210\230\346\254\241\346\225\260:", nullptr));
        yuling_button_start->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        yuling_button_pause->setText(QCoreApplication::translate("MainWindow", "\346\232\202\345\201\234", nullptr));
        yuling_button_stop->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242", nullptr));
        pages->setTabText(pages->indexOf(yulingpage), QCoreApplication::translate("MainWindow", "\345\276\241\347\201\265", nullptr));
        button_open_setting->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\350\256\276\347\275\256\347\225\214\351\235\242", nullptr));
        pages->setTabText(pages->indexOf(settingpage), QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        showInfoArea->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Ubuntu'; font-size:8pt;\">\350\276\223\345\207\272\344\277\241\346\201\257:</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Ubuntu'; font-size:8pt;\"><br /></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
