#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "comboitemmanager.h"
#include "setting.h"

#include <QComboBox>
#include <QFileDialog>
#include <QFileSystemWatcher>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QPushButton>
#include <QSharedPointer>
#include <QStandardItemModel>
#include <QString>

#define DEBUG 1
#if DEBUG
#define MINECRAFT_PATH "G:/ProgramData/ATLauncher/instances"
#else
#define MINECRAFT_PATH ""
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
} // namespace Ui

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    Ui::MainWindow *ui;

    ComboItemManager *_comboManager;

    // QStringList _versions[2];
    // QStandardItemModel *_mainModel;
    // QStandardItemModel *_followerModel;
    // int _comboxDisableCache[2] = {-1, -1};

    QFileSystemWatcher _dirWatcher;
    QList<QString> _followerFilesCache;
    QString _path[2]{MINECRAFT_PATH, MINECRAFT_PATH};
    bool _useSameAddress = true;
    bool _isFollowerListHasItem = false;

    const QString SelectFolder = "(Please Select Folder...)";
    const QString Select = "(Select...";

    void InitializeMainMenu();
    void InitMainList();
    void InitFollowerList();
    void FollowerListUpdate();
    void SetComboBoxItem(const QString &s, const std::function<void(const QFileInfo &)> &func);

    void SetComboPlaceHolder();

public slots:
    void DirectoryChanged(const QString &path);
    void OpenSetting();
    void ApplySetting(const Setting &setting);
};

#endif // MAINWINDOW_H
