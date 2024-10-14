/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *mainLayout;
    QLabel *mainLabel;
    QComboBox *mainCombo;
    QListWidget *mainList;
    QPushButton *mainButton;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *followerLayout;
    QLabel *followerLabel;
    QComboBox *followerCombo;
    QListWidget *followerList;
    QPushButton *followerButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 900);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        QFont font;
        font.setPointSize(12);
        font.setKerning(true);
        centralwidget->setFont(font);
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(20, 30, 361, 801));
        mainLayout = new QVBoxLayout(verticalLayoutWidget);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLabel = new QLabel(verticalLayoutWidget);
        mainLabel->setObjectName("mainLabel");
        mainLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        mainLayout->addWidget(mainLabel);

        mainCombo = new QComboBox(verticalLayoutWidget);
        mainCombo->setObjectName("mainCombo");

        mainLayout->addWidget(mainCombo);

        mainList = new QListWidget(verticalLayoutWidget);
        mainList->setObjectName("mainList");
        mainList->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CursorShape::ArrowCursor)));

        mainLayout->addWidget(mainList);

        mainButton = new QPushButton(verticalLayoutWidget);
        mainButton->setObjectName("mainButton");

        mainLayout->addWidget(mainButton);

        mainList->raise();
        mainLabel->raise();
        mainButton->raise();
        mainCombo->raise();
        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(410, 30, 361, 801));
        followerLayout = new QVBoxLayout(verticalLayoutWidget_2);
        followerLayout->setObjectName("followerLayout");
        followerLayout->setContentsMargins(0, 0, 0, 0);
        followerLabel = new QLabel(verticalLayoutWidget_2);
        followerLabel->setObjectName("followerLabel");
        followerLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        followerLayout->addWidget(followerLabel);

        followerCombo = new QComboBox(verticalLayoutWidget_2);
        followerCombo->setObjectName("followerCombo");
        followerCombo->setEditable(false);

        followerLayout->addWidget(followerCombo);

        followerList = new QListWidget(verticalLayoutWidget_2);
        followerList->setObjectName("followerList");

        followerLayout->addWidget(followerList);

        followerButton = new QPushButton(verticalLayoutWidget_2);
        followerButton->setObjectName("followerButton");

        followerLayout->addWidget(followerButton);

        followerList->raise();
        followerButton->raise();
        followerLabel->raise();
        followerCombo->raise();
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        followerList->setCurrentRow(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Mine Craft Mod Comparer", nullptr));
        mainLabel->setText(QCoreApplication::translate("MainWindow", "Main", nullptr));
        mainCombo->setPlaceholderText(QCoreApplication::translate("MainWindow", "(Select...)", nullptr));
        mainButton->setText(QCoreApplication::translate("MainWindow", "Select", nullptr));
        followerLabel->setText(QCoreApplication::translate("MainWindow", "Follower", nullptr));
        followerCombo->setCurrentText(QString());
        followerCombo->setPlaceholderText(QCoreApplication::translate("MainWindow", "(Select...)", nullptr));
        followerButton->setText(QCoreApplication::translate("MainWindow", "Select", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
