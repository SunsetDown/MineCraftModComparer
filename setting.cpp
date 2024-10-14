#include "setting.h"
// #include "mainwindow.h"
#include "ui_setting.h"

#include <QFileDialog>

Setting::Setting(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Setting)
{
    ui->setupUi(this);

    connect(ui->useSameAddressButton, &QRadioButton::toggled, this, &Setting::RadioButtonChanged);
    connect(ui->mainLineEdit, &QLineEdit::textChanged, this, &Setting::TextChanged);

    connect(ui->mainPushButton, &QPushButton::clicked, this, &Setting::MainAddressSelector);
    connect(ui->followerPushButton, &QPushButton::clicked, this, &Setting::FollowerAddressSelector);
}

Setting::~Setting()
{
    delete ui;
}

void Setting::SetSetting(const bool &b, const QString path[])
{
    ui->useSameAddressButton->setChecked(b);
    RadioButtonChanged(b);
    // qDebug() << path[0];
    if (b) {
        if (path[0].isEmpty())
            return;
        ui->mainLineEdit->setText(path[0]);
    } else {
        if (!path[0].isEmpty()) {
            ui->mainLineEdit->setText(path[0]);
        }
        if (!path[1].isEmpty()) {
            ui->followerLineEdit->setText(path[1]);
        }
    }
}

void Setting::RadioButtonChanged(const bool &s)
{
    // qDebug() << "debug radio button changed.";
    DisableFollower(!s);
    if (s) {
        ui->followerLineEdit->setText(ui->mainLineEdit->text());
    }
}

void Setting::DisableFollower(const bool &s)
{
    ui->followerLineEdit->setEnabled(s);
    ui->followerPushButton->setEnabled(s);
}

void Setting::TextChanged(const QString &s)
{
    if (ui->useSameAddressButton->isChecked()) {
        ui->followerLineEdit->setText(s);
    }
}

void Setting::MainAddressSelector()
{
    QString path = QFileDialog::getExistingDirectory(this, "Select Folder");
    if (!path.isEmpty())
        ui->mainLineEdit->setText(path);
}
void Setting::FollowerAddressSelector()
{
    QString path = QFileDialog::getExistingDirectory(this, "Select Folder");
    if (!path.isEmpty())
        ui->followerLineEdit->setText(path);
}

const bool Setting::IsSameChecked() const
{
    return ui->useSameAddressButton->isChecked()
           || QString::compare(GetMainAddress(), GetFollowerAddress()) == 0;
}

QString Setting::GetMainAddress() const
{
    return ui->mainLineEdit->text();
}

QString Setting::GetFollowerAddress() const
{
    return ui->followerLineEdit->text();
}
