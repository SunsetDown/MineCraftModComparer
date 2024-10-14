/********************************************************************************
** Form generated from reading UI file 'setting.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTING_H
#define UI_SETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Setting
{
public:
    QDialogButtonBox *buttonBox;
    QRadioButton *useSameAddressButton;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *mainLabel;
    QLineEdit *mainLineEdit;
    QPushButton *mainPushButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *followerLabel;
    QLineEdit *followerLineEdit;
    QPushButton *followerPushButton;

    void setupUi(QDialog *Setting)
    {
        if (Setting->objectName().isEmpty())
            Setting->setObjectName("Setting");
        Setting->resize(640, 300);
        buttonBox = new QDialogButtonBox(Setting);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(280, 240, 341, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        useSameAddressButton = new QRadioButton(Setting);
        useSameAddressButton->setObjectName("useSameAddressButton");
        useSameAddressButton->setGeometry(QRect(20, 160, 141, 21));
        useSameAddressButton->setChecked(true);
        verticalLayoutWidget = new QWidget(Setting);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(20, 20, 601, 121));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        mainLabel = new QLabel(verticalLayoutWidget);
        mainLabel->setObjectName("mainLabel");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mainLabel->sizePolicy().hasHeightForWidth());
        mainLabel->setSizePolicy(sizePolicy);
        mainLabel->setMinimumSize(QSize(60, 0));
        mainLabel->setTextFormat(Qt::TextFormat::PlainText);
        mainLabel->setScaledContents(false);
        mainLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        mainLabel->setWordWrap(false);
        mainLabel->setMargin(0);

        horizontalLayout->addWidget(mainLabel);

        mainLineEdit = new QLineEdit(verticalLayoutWidget);
        mainLineEdit->setObjectName("mainLineEdit");

        horizontalLayout->addWidget(mainLineEdit);

        mainPushButton = new QPushButton(verticalLayoutWidget);
        mainPushButton->setObjectName("mainPushButton");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(mainPushButton->sizePolicy().hasHeightForWidth());
        mainPushButton->setSizePolicy(sizePolicy1);
        mainPushButton->setMaximumSize(QSize(30, 16777215));

        horizontalLayout->addWidget(mainPushButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        followerLabel = new QLabel(verticalLayoutWidget);
        followerLabel->setObjectName("followerLabel");
        sizePolicy.setHeightForWidth(followerLabel->sizePolicy().hasHeightForWidth());
        followerLabel->setSizePolicy(sizePolicy);
        followerLabel->setMinimumSize(QSize(60, 0));
        followerLabel->setTextFormat(Qt::TextFormat::PlainText);
        followerLabel->setScaledContents(false);
        followerLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        followerLabel->setWordWrap(false);
        followerLabel->setMargin(0);

        horizontalLayout_2->addWidget(followerLabel);

        followerLineEdit = new QLineEdit(verticalLayoutWidget);
        followerLineEdit->setObjectName("followerLineEdit");

        horizontalLayout_2->addWidget(followerLineEdit);

        followerPushButton = new QPushButton(verticalLayoutWidget);
        followerPushButton->setObjectName("followerPushButton");
        sizePolicy1.setHeightForWidth(followerPushButton->sizePolicy().hasHeightForWidth());
        followerPushButton->setSizePolicy(sizePolicy1);
        followerPushButton->setMaximumSize(QSize(30, 16777215));

        horizontalLayout_2->addWidget(followerPushButton);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(Setting);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Setting, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Setting, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Setting);
    } // setupUi

    void retranslateUi(QDialog *Setting)
    {
        Setting->setWindowTitle(QCoreApplication::translate("Setting", "Setting", nullptr));
        useSameAddressButton->setText(QCoreApplication::translate("Setting", "Use Same Address", nullptr));
        mainLabel->setText(QCoreApplication::translate("Setting", "Main: ", nullptr));
        mainPushButton->setText(QCoreApplication::translate("Setting", "...", nullptr));
        followerLabel->setText(QCoreApplication::translate("Setting", "Follower: ", nullptr));
        followerPushButton->setText(QCoreApplication::translate("Setting", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Setting: public Ui_Setting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTING_H
