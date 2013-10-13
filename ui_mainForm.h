/********************************************************************************
** Form generated from reading UI file 'mainForm.ui'
**
** Created: Sun 13. Oct 12:57:37 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_mainForm
{
public:
    QPushButton *pushbuttonEncode;
    QProgressBar *progressbarEncode;
    QLineEdit *lineeditUserFileInput;
    QToolButton *toolbuttonUserFileInput;
    QLineEdit *lineeditBasename;
    QToolButton *toolbuttonBasename;
    QGroupBox *groupboxToDoList;
    QCheckBox *checkboxPreview;
    QCheckBox *checkbox360;
    QCheckBox *checkbox720;
    QCheckBox *checkbox1080;
    QCheckBox *checkboxUserDefined;
    QGroupBox *groupboxSetupPreview;
    QLabel *labelPreviewAt;
    QDoubleSpinBox *doublespinboxUserPreviewTime;
    QLabel *labelSeconds;
    QToolButton *toolbuttonUserPreviewTime;
    QGroupBox *groupboxSetupUserDefined;
    QLabel *labelResizeTo;
    QLabel *labelX;
    QLabel *labelKeepOnly;
    QLabel *labelPoints;
    QDoubleSpinBox *doublespinboxUserCutTimeStart;
    QDoubleSpinBox *doublespinboxUserCutTimeStop;
    QSpinBox *spinboxUserResizeResolutionX;
    QSpinBox *spinboxUserResizeResolutionY;

    void setupUi(QDialog *mainForm)
    {
        if (mainForm->objectName().isEmpty())
            mainForm->setObjectName(QString::fromUtf8("mainForm"));
        mainForm->resize(311, 552);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mainForm->sizePolicy().hasHeightForWidth());
        mainForm->setSizePolicy(sizePolicy);
        mainForm->setMinimumSize(QSize(0, 0));
        mainForm->setCursor(QCursor(Qt::ArrowCursor));
        pushbuttonEncode = new QPushButton(mainForm);
        pushbuttonEncode->setObjectName(QString::fromUtf8("pushbuttonEncode"));
        pushbuttonEncode->setGeometry(QRect(220, 520, 75, 23));
        progressbarEncode = new QProgressBar(mainForm);
        progressbarEncode->setObjectName(QString::fromUtf8("progressbarEncode"));
        progressbarEncode->setEnabled(true);
        progressbarEncode->setGeometry(QRect(10, 520, 201, 16));
        progressbarEncode->setValue(0);
        progressbarEncode->setTextVisible(false);
        progressbarEncode->setOrientation(Qt::Horizontal);
        lineeditUserFileInput = new QLineEdit(mainForm);
        lineeditUserFileInput->setObjectName(QString::fromUtf8("lineeditUserFileInput"));
        lineeditUserFileInput->setGeometry(QRect(20, 20, 241, 20));
        lineeditUserFileInput->setReadOnly(true);
        toolbuttonUserFileInput = new QToolButton(mainForm);
        toolbuttonUserFileInput->setObjectName(QString::fromUtf8("toolbuttonUserFileInput"));
        toolbuttonUserFileInput->setGeometry(QRect(270, 20, 25, 19));
        lineeditBasename = new QLineEdit(mainForm);
        lineeditBasename->setObjectName(QString::fromUtf8("lineeditBasename"));
        lineeditBasename->setGeometry(QRect(20, 60, 241, 20));
        toolbuttonBasename = new QToolButton(mainForm);
        toolbuttonBasename->setObjectName(QString::fromUtf8("toolbuttonBasename"));
        toolbuttonBasename->setGeometry(QRect(270, 60, 25, 19));
        groupboxToDoList = new QGroupBox(mainForm);
        groupboxToDoList->setObjectName(QString::fromUtf8("groupboxToDoList"));
        groupboxToDoList->setGeometry(QRect(20, 100, 271, 191));
        checkboxPreview = new QCheckBox(groupboxToDoList);
        checkboxPreview->setObjectName(QString::fromUtf8("checkboxPreview"));
        checkboxPreview->setGeometry(QRect(20, 30, 261, 21));
        checkbox360 = new QCheckBox(groupboxToDoList);
        checkbox360->setObjectName(QString::fromUtf8("checkbox360"));
        checkbox360->setGeometry(QRect(20, 60, 261, 21));
        checkbox720 = new QCheckBox(groupboxToDoList);
        checkbox720->setObjectName(QString::fromUtf8("checkbox720"));
        checkbox720->setEnabled(true);
        checkbox720->setGeometry(QRect(20, 90, 121, 21));
        checkbox1080 = new QCheckBox(groupboxToDoList);
        checkbox1080->setObjectName(QString::fromUtf8("checkbox1080"));
        checkbox1080->setGeometry(QRect(20, 120, 161, 17));
        checkboxUserDefined = new QCheckBox(groupboxToDoList);
        checkboxUserDefined->setObjectName(QString::fromUtf8("checkboxUserDefined"));
        checkboxUserDefined->setGeometry(QRect(20, 150, 211, 17));
        groupboxSetupPreview = new QGroupBox(mainForm);
        groupboxSetupPreview->setObjectName(QString::fromUtf8("groupboxSetupPreview"));
        groupboxSetupPreview->setGeometry(QRect(20, 309, 271, 71));
        labelPreviewAt = new QLabel(groupboxSetupPreview);
        labelPreviewAt->setObjectName(QString::fromUtf8("labelPreviewAt"));
        labelPreviewAt->setGeometry(QRect(20, 30, 61, 16));
        doublespinboxUserPreviewTime = new QDoubleSpinBox(groupboxSetupPreview);
        doublespinboxUserPreviewTime->setObjectName(QString::fromUtf8("doublespinboxUserPreviewTime"));
        doublespinboxUserPreviewTime->setEnabled(false);
        doublespinboxUserPreviewTime->setGeometry(QRect(80, 30, 71, 22));
        doublespinboxUserPreviewTime->setLayoutDirection(Qt::LeftToRight);
        doublespinboxUserPreviewTime->setAutoFillBackground(false);
        doublespinboxUserPreviewTime->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doublespinboxUserPreviewTime->setMaximum(100000);
        labelSeconds = new QLabel(groupboxSetupPreview);
        labelSeconds->setObjectName(QString::fromUtf8("labelSeconds"));
        labelSeconds->setGeometry(QRect(160, 30, 46, 13));
        toolbuttonUserPreviewTime = new QToolButton(groupboxSetupPreview);
        toolbuttonUserPreviewTime->setObjectName(QString::fromUtf8("toolbuttonUserPreviewTime"));
        toolbuttonUserPreviewTime->setEnabled(false);
        toolbuttonUserPreviewTime->setGeometry(QRect(220, 30, 25, 19));
        groupboxSetupUserDefined = new QGroupBox(mainForm);
        groupboxSetupUserDefined->setObjectName(QString::fromUtf8("groupboxSetupUserDefined"));
        groupboxSetupUserDefined->setGeometry(QRect(20, 400, 271, 101));
        labelResizeTo = new QLabel(groupboxSetupUserDefined);
        labelResizeTo->setObjectName(QString::fromUtf8("labelResizeTo"));
        labelResizeTo->setGeometry(QRect(20, 30, 51, 16));
        labelX = new QLabel(groupboxSetupUserDefined);
        labelX->setObjectName(QString::fromUtf8("labelX"));
        labelX->setGeometry(QRect(170, 30, 16, 16));
        labelKeepOnly = new QLabel(groupboxSetupUserDefined);
        labelKeepOnly->setObjectName(QString::fromUtf8("labelKeepOnly"));
        labelKeepOnly->setGeometry(QRect(20, 60, 61, 16));
        labelPoints = new QLabel(groupboxSetupUserDefined);
        labelPoints->setObjectName(QString::fromUtf8("labelPoints"));
        labelPoints->setGeometry(QRect(170, 60, 16, 16));
        doublespinboxUserCutTimeStart = new QDoubleSpinBox(groupboxSetupUserDefined);
        doublespinboxUserCutTimeStart->setObjectName(QString::fromUtf8("doublespinboxUserCutTimeStart"));
        doublespinboxUserCutTimeStart->setEnabled(false);
        doublespinboxUserCutTimeStart->setGeometry(QRect(90, 60, 71, 22));
        doublespinboxUserCutTimeStart->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doublespinboxUserCutTimeStart->setMaximum(100000);
        doublespinboxUserCutTimeStop = new QDoubleSpinBox(groupboxSetupUserDefined);
        doublespinboxUserCutTimeStop->setObjectName(QString::fromUtf8("doublespinboxUserCutTimeStop"));
        doublespinboxUserCutTimeStop->setEnabled(false);
        doublespinboxUserCutTimeStop->setGeometry(QRect(181, 60, 71, 22));
        doublespinboxUserCutTimeStop->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doublespinboxUserCutTimeStop->setMaximum(100000);
        doublespinboxUserCutTimeStop->setValue(99999);
        spinboxUserResizeResolutionX = new QSpinBox(groupboxSetupUserDefined);
        spinboxUserResizeResolutionX->setObjectName(QString::fromUtf8("spinboxUserResizeResolutionX"));
        spinboxUserResizeResolutionX->setEnabled(false);
        spinboxUserResizeResolutionX->setGeometry(QRect(90, 30, 71, 22));
        spinboxUserResizeResolutionX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinboxUserResizeResolutionX->setMaximum(9999999);
        spinboxUserResizeResolutionY = new QSpinBox(groupboxSetupUserDefined);
        spinboxUserResizeResolutionY->setObjectName(QString::fromUtf8("spinboxUserResizeResolutionY"));
        spinboxUserResizeResolutionY->setEnabled(false);
        spinboxUserResizeResolutionY->setGeometry(QRect(180, 30, 71, 22));
        spinboxUserResizeResolutionY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinboxUserResizeResolutionY->setMaximum(9999999);

        retranslateUi(mainForm);

        QMetaObject::connectSlotsByName(mainForm);
    } // setupUi

    void retranslateUi(QDialog *mainForm)
    {
        mainForm->setWindowTitle(QApplication::translate("mainForm", "Take Your Pills Video Encoder", 0, QApplication::UnicodeUTF8));
        pushbuttonEncode->setText(QApplication::translate("mainForm", "Encode !", 0, QApplication::UnicodeUTF8));
        lineeditUserFileInput->setText(QString());
        lineeditUserFileInput->setPlaceholderText(QApplication::translate("mainForm", "Select a video file", 0, QApplication::UnicodeUTF8));
        toolbuttonUserFileInput->setText(QApplication::translate("mainForm", "...", 0, QApplication::UnicodeUTF8));
        lineeditBasename->setText(QString());
        lineeditBasename->setPlaceholderText(QApplication::translate("mainForm", "Enter a basename", 0, QApplication::UnicodeUTF8));
        toolbuttonBasename->setText(QApplication::translate("mainForm", "?", 0, QApplication::UnicodeUTF8));
        groupboxToDoList->setTitle(QApplication::translate("mainForm", "To-Do List", 0, QApplication::UnicodeUTF8));
        checkboxPreview->setText(QApplication::translate("mainForm", "Preview", 0, QApplication::UnicodeUTF8));
        checkbox360->setText(QApplication::translate("mainForm", "Standard Definition (360)", 0, QApplication::UnicodeUTF8));
        checkbox720->setText(QApplication::translate("mainForm", "High Definition (720)", 0, QApplication::UnicodeUTF8));
        checkbox1080->setText(QApplication::translate("mainForm", "High Definition (1080)", 0, QApplication::UnicodeUTF8));
        checkboxUserDefined->setText(QApplication::translate("mainForm", "User-defined video", 0, QApplication::UnicodeUTF8));
        groupboxSetupPreview->setTitle(QApplication::translate("mainForm", "Setup preview", 0, QApplication::UnicodeUTF8));
        labelPreviewAt->setText(QApplication::translate("mainForm", "Preview at", 0, QApplication::UnicodeUTF8));
        labelSeconds->setText(QApplication::translate("mainForm", "seconds", 0, QApplication::UnicodeUTF8));
        toolbuttonUserPreviewTime->setText(QApplication::translate("mainForm", "...", 0, QApplication::UnicodeUTF8));
        groupboxSetupUserDefined->setTitle(QApplication::translate("mainForm", "Setup user-defined video", 0, QApplication::UnicodeUTF8));
        labelResizeTo->setText(QApplication::translate("mainForm", "Resize to", 0, QApplication::UnicodeUTF8));
        labelX->setText(QApplication::translate("mainForm", "x", 0, QApplication::UnicodeUTF8));
        labelKeepOnly->setText(QApplication::translate("mainForm", "Keep only", 0, QApplication::UnicodeUTF8));
        labelPoints->setText(QApplication::translate("mainForm", ":", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class mainForm: public Ui_mainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
