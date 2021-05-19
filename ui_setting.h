/********************************************************************************
** Form generated from reading UI file 'setting.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTING_H
#define UI_SETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_setting
{
public:
    QGroupBox *groupBox;
    QRadioButton *resolution1;
    QRadioButton *resolution2;
    QGroupBox *groupBox_2;
    QCheckBox *check_addOtherOperations;
    QLabel *label_jiejiePropCount;
    QCheckBox *check_autoPrepare;
    QCheckBox *check_stopWhenFail;
    QLineEdit *edit_jiejiePropCount;
    QCheckBox *check_popupWhenStop;
    QCheckBox *check_stopWhenLimit;
    QCheckBox *check_autoUpdate;
    QGroupBox *groupBox_3;
    QCheckBox *check_magatama30;
    QCheckBox *check_strength30;
    QCheckBox *check_gold2w;
    QCheckBox *check_gold3w;
    QPushButton *button_ok;
    QPushButton *button_exit;

    void setupUi(QWidget *setting)
    {
        if (setting->objectName().isEmpty())
            setting->setObjectName(QString::fromUtf8("setting"));
        setting->resize(530, 450);
        groupBox = new QGroupBox(setting);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(30, 20, 201, 81));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(10);
        groupBox->setFont(font);
        resolution1 = new QRadioButton(groupBox);
        resolution1->setObjectName(QString::fromUtf8("resolution1"));
        resolution1->setGeometry(QRect(10, 20, 153, 22));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(11);
        resolution1->setFont(font1);
        resolution1->setCheckable(true);
        resolution1->setChecked(false);
        resolution2 = new QRadioButton(groupBox);
        resolution2->setObjectName(QString::fromUtf8("resolution2"));
        resolution2->setGeometry(QRect(10, 50, 151, 22));
        resolution2->setFont(font1);
        resolution2->setChecked(true);
        groupBox_2 = new QGroupBox(setting);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(30, 120, 471, 251));
        groupBox_2->setFont(font);
        check_addOtherOperations = new QCheckBox(groupBox_2);
        check_addOtherOperations->setObjectName(QString::fromUtf8("check_addOtherOperations"));
        check_addOtherOperations->setEnabled(true);
        check_addOtherOperations->setGeometry(QRect(20, 60, 189, 25));
        check_addOtherOperations->setFont(font1);
        check_addOtherOperations->setChecked(false);
        label_jiejiePropCount = new QLabel(groupBox_2);
        label_jiejiePropCount->setObjectName(QString::fromUtf8("label_jiejiePropCount"));
        label_jiejiePropCount->setGeometry(QRect(42, 150, 181, 25));
        label_jiejiePropCount->setFont(font1);
        check_autoPrepare = new QCheckBox(groupBox_2);
        check_autoPrepare->setObjectName(QString::fromUtf8("check_autoPrepare"));
        check_autoPrepare->setGeometry(QRect(20, 30, 151, 19));
        check_autoPrepare->setFont(font1);
        check_stopWhenFail = new QCheckBox(groupBox_2);
        check_stopWhenFail->setObjectName(QString::fromUtf8("check_stopWhenFail"));
        check_stopWhenFail->setGeometry(QRect(20, 90, 211, 25));
        check_stopWhenFail->setFont(font1);
        check_stopWhenFail->setChecked(false);
        edit_jiejiePropCount = new QLineEdit(groupBox_2);
        edit_jiejiePropCount->setObjectName(QString::fromUtf8("edit_jiejiePropCount"));
        edit_jiejiePropCount->setGeometry(QRect(220, 152, 60, 21));
        check_popupWhenStop = new QCheckBox(groupBox_2);
        check_popupWhenStop->setObjectName(QString::fromUtf8("check_popupWhenStop"));
        check_popupWhenStop->setGeometry(QRect(20, 180, 201, 25));
        check_popupWhenStop->setFont(font1);
        check_stopWhenLimit = new QCheckBox(groupBox_2);
        check_stopWhenLimit->setObjectName(QString::fromUtf8("check_stopWhenLimit"));
        check_stopWhenLimit->setGeometry(QRect(20, 120, 243, 25));
        check_stopWhenLimit->setFont(font1);
        check_stopWhenLimit->setChecked(false);
        check_autoUpdate = new QCheckBox(groupBox_2);
        check_autoUpdate->setObjectName(QString::fromUtf8("check_autoUpdate"));
        check_autoUpdate->setGeometry(QRect(20, 210, 201, 25));
        check_autoUpdate->setFont(font1);
        groupBox_3 = new QGroupBox(setting);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(270, 20, 231, 81));
        check_magatama30 = new QCheckBox(groupBox_3);
        check_magatama30->setObjectName(QString::fromUtf8("check_magatama30"));
        check_magatama30->setGeometry(QRect(20, 20, 91, 19));
        check_magatama30->setFont(font1);
        check_strength30 = new QCheckBox(groupBox_3);
        check_strength30->setObjectName(QString::fromUtf8("check_strength30"));
        check_strength30->setGeometry(QRect(120, 20, 91, 19));
        check_strength30->setFont(font1);
        check_gold2w = new QCheckBox(groupBox_3);
        check_gold2w->setObjectName(QString::fromUtf8("check_gold2w"));
        check_gold2w->setGeometry(QRect(20, 50, 91, 19));
        check_gold2w->setFont(font1);
        check_gold3w = new QCheckBox(groupBox_3);
        check_gold3w->setObjectName(QString::fromUtf8("check_gold3w"));
        check_gold3w->setGeometry(QRect(120, 50, 91, 19));
        check_gold3w->setFont(font1);
        button_ok = new QPushButton(setting);
        button_ok->setObjectName(QString::fromUtf8("button_ok"));
        button_ok->setGeometry(QRect(130, 400, 90, 28));
        button_exit = new QPushButton(setting);
        button_exit->setObjectName(QString::fromUtf8("button_exit"));
        button_exit->setGeometry(QRect(290, 400, 90, 28));

        retranslateUi(setting);

        QMetaObject::connectSlotsByName(setting);
    } // setupUi

    void retranslateUi(QWidget *setting)
    {
        setting->setWindowTitle(QCoreApplication::translate("setting", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("setting", "\345\210\206\350\276\250\347\216\207", nullptr));
        resolution1->setText(QCoreApplication::translate("setting", "1440*849(\351\273\230\350\256\244)", nullptr));
        resolution2->setText(QCoreApplication::translate("setting", "961*579 (\346\216\250\350\215\220)", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("setting", "\346\210\230\346\226\227\350\256\276\347\275\256", nullptr));
        check_addOtherOperations->setText(QCoreApplication::translate("setting", "\346\210\230\346\226\227\346\227\266\346\267\273\345\212\240\351\232\217\346\234\272\346\223\215\344\275\234", nullptr));
        label_jiejiePropCount->setText(QCoreApplication::translate("setting", "\345\211\251\344\275\231\347\273\223\347\225\214\347\252\201\347\240\264\345\210\270\346\225\260\351\207\217:", nullptr));
        check_autoPrepare->setText(QCoreApplication::translate("setting", "\345\274\200\345\261\200\350\207\252\345\212\250\345\207\206\345\244\207", nullptr));
        check_stopWhenFail->setText(QCoreApplication::translate("setting", "\346\210\230\346\226\227\345\244\261\350\264\245\346\227\266\344\270\215\345\201\234\346\255\242\347\250\213\345\272\217", nullptr));
        edit_jiejiePropCount->setText(QCoreApplication::translate("setting", "0", nullptr));
        check_popupWhenStop->setText(QCoreApplication::translate("setting", "\347\250\213\345\272\217\345\201\234\346\255\242\346\227\266\345\274\271\347\252\227\346\217\220\347\244\272", nullptr));
        check_stopWhenLimit->setText(QCoreApplication::translate("setting", "\347\273\223\347\225\214\347\252\201\347\240\264\345\210\270\350\276\276\345\210\260\344\270\212\351\231\220\346\227\266\345\201\234\346\255\242", nullptr));
        check_autoUpdate->setText(QCoreApplication::translate("setting", "\346\257\217\346\254\241\345\220\257\345\212\250\346\227\266\346\243\200\346\265\213\346\233\264\346\226\260", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("setting", "\345\215\217\344\275\234", nullptr));
        check_magatama30->setText(QCoreApplication::translate("setting", "\345\213\276\345\215\217", nullptr));
        check_strength30->setText(QCoreApplication::translate("setting", "30\344\275\223\345\212\233", nullptr));
        check_gold2w->setText(QCoreApplication::translate("setting", "2W\351\207\221\345\270\201", nullptr));
        check_gold3w->setText(QCoreApplication::translate("setting", "3W\351\207\221\345\270\201", nullptr));
        button_ok->setText(QCoreApplication::translate("setting", "\347\241\256\345\256\232", nullptr));
        button_exit->setText(QCoreApplication::translate("setting", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class setting: public Ui_setting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTING_H
