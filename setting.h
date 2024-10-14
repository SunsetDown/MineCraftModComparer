#ifndef SETTING_H
#define SETTING_H

#include <QDialog>

namespace Ui {
class Setting;
}

class Setting : public QDialog
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();

    const bool IsSameChecked() const;

    QString GetMainAddress() const;
    QString GetFollowerAddress() const;

    void SetSetting(const bool &b, const QString path[]);
    // void SetSetting(const bool &b, const QString path[]);

private:
    Ui::Setting *ui;

    void DisableFollower(const bool &s);

private slots:
    void RadioButtonChanged(const bool &s);
    void TextChanged(const QString &s);
    void MainAddressSelector();
    void FollowerAddressSelector();
};

#endif // SETTING_H
