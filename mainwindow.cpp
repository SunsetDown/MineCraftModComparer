#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "listitem.h"

#define DISABLE_COMBO_DATA QVariant(0)
#define ENABLE_COMBO_DATA QVariant(33)

static void GetFileNameToQList(const QString &path, const std::function<void(QString)> &func);

QList<QSharedPointer<ListItem>> manager;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _comboManager = new ComboItemManager(ui->mainCombo, ui->followerCombo);

    auto *settingMenu = menuBar()->addMenu(tr("setting"));
    QAction *setting = settingMenu->addAction(tr("setting"));
    connect(setting, &QAction::triggered, this, &MainWindow::OpenSetting);

    ui->mainButton->installEventFilter(this);

    connect(ui->mainButton, &QPushButton::clicked, [](bool checked) {
        qDebug() << "button clicked. " << checked;
    });

    InitializeMainMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _comboManager;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonRelease) {
        qDebug() << "debug mouse release evnet.";
        return false;
    }
    if (event->type() == QEvent::MouseButtonPress) {
        qDebug() << "debug mouse press evnet. ";
        return true;
    }
    // qDebug() << "debug event continue." << obj->objectName() << event->type();
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::InitializeMainMenu()
{
    // 初始化下拉选项，并记录model方便后续更改选择后的外观
    SetComboBoxItem(_path[0], [this](const QFileInfo &f) {
        _comboManager->AddVersion(ComboItemManager::main, f.filePath());
        _comboManager->AddVersion(ComboItemManager::follower, f.filePath());
        // _versions[0].append(f.filePath());
        // _versions[1].append(f.filePath());
        ui->mainCombo->addItem(f.fileName());
        ui->followerCombo->addItem(f.fileName());
    });
    _comboManager->SetModel(ComboItemManager::main,
                            qobject_cast<QStandardItemModel *>(ui->mainCombo->model()));
    _comboManager->SetModel(ComboItemManager::follower,
                            qobject_cast<QStandardItemModel *>(ui->followerCombo->model()));
    // _mainModel = qobject_cast<QStandardItemModel *>(ui->mainCombo->model());
    // _followerModel = qobject_cast<QStandardItemModel *>(ui->followerCombo->model());

    connect(&_dirWatcher,
            &QFileSystemWatcher::directoryChanged,
            this,
            &MainWindow::DirectoryChanged);

    InitMainList();
    InitFollowerList();
}

void MainWindow::SetComboBoxItem(const QString &s,
                                 const std::function<void(const QFileInfo &)> &func)
{
    if (s.isEmpty())
        return;

    QDir dir(s);
    if (!dir.exists())
        return;

    QFileInfoList allFiles = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (const auto &file : allFiles)
        func(file);
}

void MainWindow::DirectoryChanged(const QString &path)
{
    qDebug() << "directory has changed, " << path;
    GetFileNameToQList(path, [this](QString modName) {
        if (_followerFilesCache.contains(modName))
            return;
        auto [isContain, containPtr] = ListItem::TryGet(manager, modName);
        if (isContain) {
            QListWidgetItem *cloneItem = containPtr->MakeClone();
            ui->followerList->addItem(cloneItem);
            containPtr->setState(ListItem::same);
        } else {
            QListWidgetItem *item = new QListWidgetItem(modName);
            auto listItem = QSharedPointer<ListItem>(new ListItem(item, modName));
            listItem->setState(ListItem::extra);
            ui->followerList->addItem(item);
            manager.append(listItem);
        }
        _followerFilesCache.append(modName);
    });
}

void MainWindow::InitMainList()
{
    connect(ui->mainCombo, &QComboBox::currentIndexChanged, this, [this](int index) {
        if (index < 0 || index >= ui->followerCombo->count())
            return;
        // 设置下拉选择样式，以及禁用已选择下拉选项
        if (_comboManager->HasStateChanged(ComboItemManager::main)) {
            const int &oldIndex = _comboManager->GetIndexCache(ComboItemManager::main);
            if (_useSameAddress) {
                _comboManager->SetNormal(ComboItemManager::follower, oldIndex);
            }
            _comboManager->SetNormal(ComboItemManager::main, oldIndex);
        }
        if (_useSameAddress) {
            _comboManager->SetState(ComboItemManager::follower, ComboItemManager::disabled, index);
        }
        _comboManager->SetState(ComboItemManager::main, ComboItemManager::onSelected, index);

        // 清除list，并选择下拉选项时将选择的版本中的mods文件夹中的mod文件处理并添加到list中
        ui->mainList->clear();
        manager.clear();

        const QString &path = _comboManager->GetVersion(ComboItemManager::main, index);

        GetFileNameToQList(/*_versions[0].at(index)*/ path, [this](QString modName) {
            QListWidgetItem *item = new QListWidgetItem(modName);
            ui->mainList->addItem(item);
            manager.append(QSharedPointer<ListItem>(new ListItem(item, modName)));
        });
        if (_isFollowerListHasItem)
            FollowerListUpdate();
    });
}

void MainWindow::InitFollowerList()
{
    connect(ui->followerCombo, &QComboBox::currentIndexChanged, this, [this](int index) {
        if (index < 0 || index >= ui->followerCombo->count())
            return;
        // qDebug() << "Debug: " << index;
        // 设置下拉选择样式，以及禁用已选择下拉选项,同时开始监听文件夹内文件变化
        if (_comboManager->HasStateChanged(ComboItemManager::follower)) {
            const int &oldIndex = _comboManager->GetIndexCache(ComboItemManager::follower);
            if (_useSameAddress) {
                _comboManager->SetNormal(ComboItemManager::main, oldIndex);
            }
            _comboManager->SetNormal(ComboItemManager::follower, oldIndex);

            _dirWatcher.removePath(_comboManager->GetVersion(ComboItemManager::follower, oldIndex));
        }
        if (_useSameAddress) {
            _comboManager->SetState(ComboItemManager::main, ComboItemManager::disabled, index);
        }

        _comboManager->SetState(ComboItemManager::follower, ComboItemManager::onSelected, index);

        _dirWatcher.addPath(_comboManager->GetVersion(ComboItemManager::follower, index));

        FollowerListUpdate();
    });
}

void MainWindow::FollowerListUpdate()
{
    const int &index = _comboManager->GetIndexCache(ComboItemManager::follower);
    const QString &path = _comboManager->GetVersion(ComboItemManager::follower, index);
    // 初始化manager，清空_followerFilesCache
    ListItem::Clear(manager);
    _followerFilesCache.clear();

    // 清除list，并选择下拉选项时将选择的版本中的mods文件夹中的mod文件处理并添加到list中
    ui->followerList->clear();
    GetFileNameToQList(path, [this](QString modName) {
        _followerFilesCache.append(modName);
        auto [isContain, containPtr] = ListItem::TryGet(manager, modName);
        if (isContain) {
            QListWidgetItem *cloneItem = containPtr->MakeClone();
            ui->followerList->addItem(cloneItem);
            containPtr->setState(ListItem::same);
        } else {
            QListWidgetItem *item = new QListWidgetItem(modName);
            auto listItem = QSharedPointer<ListItem>(new ListItem(item, modName));
            listItem->setState(ListItem::extra);
            ui->followerList->addItem(item);
            manager.append(listItem);
        }
        // qDebug() << ((ListItem) manager.at(0) == (ListItem) manager.at(0));
    });

    // 将state为_default的item设置state为non_same
    for (auto item : manager) {
        if (item->getState() == ListItem::_default) {
            item->setState(ListItem::non_same);
        }
    }

    _isFollowerListHasItem = _followerFilesCache.count() > 0;

    // qDebug() << manager.size();
}

void MainWindow::OpenSetting()
{
    Setting setting;
    setting.SetSetting(_useSameAddress, _path);

    if (setting.exec() == 0)
        return;

    ApplySetting(setting);
}

void MainWindow::ApplySetting(const Setting &setting)
{
    _useSameAddress = setting.IsSameChecked();

    if (_useSameAddress) {
        QString s = setting.GetMainAddress();

        if (QString::compare(s, _path[0]) == 0 && QString::compare(s, _path[1]) == 0)
            return;

        // 清空 versions 缓存和下拉选项
        _comboManager->ClearVersion(ComboItemManager::main);
        _comboManager->ClearVersion(ComboItemManager::follower);
        // _versions[0].clear();
        ui->mainCombo->clear();
        // _versions[1].clear();
        ui->followerCombo->clear();

        // 设置下拉选项，更新 _path 缓存，更新 versions 缓存
        SetComboBoxItem(s, [this](const QFileInfo &f) {
            _comboManager->AddVersion(ComboItemManager::main, f.filePath());
            _comboManager->AddVersion(ComboItemManager::follower, f.filePath());
            ui->mainCombo->addItem(f.fileName());
            ui->followerCombo->addItem(f.fileName());
        });
        _path[0] = s;
        _path[1] = s;

        //更新 model 缓存
        _comboManager->SetModel(ComboItemManager::main,
                                qobject_cast<QStandardItemModel *>(ui->mainCombo->model()));
        _comboManager->SetModel(ComboItemManager::follower,
                                qobject_cast<QStandardItemModel *>(ui->followerCombo->model()));

        // 清空 main 和 follower ListWidget，并清空 manager
        ui->mainList->clear();
        ui->followerList->clear();
        manager.clear();
        _followerFilesCache.clear();
        _isFollowerListHasItem = _followerFilesCache.count() > 0;
    } else {
        QString s1 = setting.GetMainAddress(), s2 = setting.GetFollowerAddress();
        bool b1 = QString::compare(s1, _path[0]) != 0, b2 = QString::compare(s2, _path[1]) != 0;

        if (b1 && b2) {
            // main 和 follower 地址都改变了
            // 清空 main versions 缓存和下拉选项
            _comboManager->ClearVersion(ComboItemManager::main);
            ui->mainCombo->clear();

            // 设置 main下拉选项
            SetComboBoxItem(s1, [this](const QFileInfo &s) {
                ui->mainCombo->addItem(s.fileName());
                _comboManager->AddVersion(ComboItemManager::main, s.filePath());
            });

            // 清空 follower versions 缓存和下拉选项
            _comboManager->ClearVersion(ComboItemManager::follower);
            ui->followerCombo->clear();

            // 设置 follower下拉选项
            SetComboBoxItem(s2, [this](const QFileInfo &s) {
                ui->followerCombo->addItem(s.fileName());
                _comboManager->AddVersion(ComboItemManager::follower, s.filePath());
            });

            // 设置 main 和 follower 的 _path 缓存和 model 缓存
            _path[0] = s1;
            _path[1] = s2;
            _comboManager->SetModel(ComboItemManager::main,
                                    qobject_cast<QStandardItemModel *>(ui->mainCombo->model()));
            _comboManager->SetModel(ComboItemManager::follower,
                                    qobject_cast<QStandardItemModel *>(ui->followerCombo->model()));

            // 清空 main 和 follower ListWidget，并清空 manager
            ui->mainList->clear();
            ui->followerList->clear();
            manager.clear();
            _followerFilesCache.clear();
            _isFollowerListHasItem = _followerFilesCache.count() > 0;
        } else if (b1) {
            // main 地址改变了
            // deal <main>
            ui->mainCombo->clear();
            _comboManager->ClearVersion(ComboItemManager::main);

            SetComboBoxItem(s1, [this](const QFileInfo &s) {
                ui->mainCombo->addItem(s.fileName());
                _comboManager->AddVersion(ComboItemManager::main, s.filePath());
            });

            _path[0] = s1;
            _comboManager->SetModel(ComboItemManager::main,
                                    qobject_cast<QStandardItemModel *>(ui->mainCombo->model()));

            if (_isFollowerListHasItem)
                FollowerListUpdate();
            ui->mainList->clear();
        } else if (b2) {
            // follower 地址改变了
            // deal <follower>
            ui->followerCombo->clear();
            _comboManager->ClearVersion(ComboItemManager::follower);

            SetComboBoxItem(s2, [this](const QFileInfo &s) {
                ui->followerCombo->addItem(s.fileName());
                _comboManager->AddVersion(ComboItemManager::follower, s.filePath());
            });

            _path[1] = s2;
            _comboManager->SetModel(ComboItemManager::follower,
                                    qobject_cast<QStandardItemModel *>(ui->followerCombo->model()));

            // 清空 main 和 follower ListWidget，并清空 manager
            ListItem::Clear(manager);
            ui->followerList->clear();
            _followerFilesCache.clear();
            _isFollowerListHasItem = _followerFilesCache.count() > 0;
        } else {
            // main 和 follower 地址都没有改变
            return;
        }
    }
    SetComboPlaceHolder();
}

void MainWindow::SetComboPlaceHolder()
{
    // 检测 main version 是否是空的
    if (_comboManager->GetVersionCount(ComboItemManager::main) > 0)
        ui->mainCombo->setPlaceholderText(Select);
    else
        ui->mainCombo->setPlaceholderText(SelectFolder);

    // 检测 follower version 是否是空的
    if (_comboManager->GetVersionCount(ComboItemManager::follower) > 0)
        ui->followerCombo->setPlaceholderText(Select);
    else
        ui->followerCombo->setPlaceholderText(SelectFolder);
}

static void GetFileNameToQList(const QString &path, const std::function<void(QString)> &func)
{
    if (path.isEmpty())
        return;
    // qDebug() << saveToCache;
    QDir dir(path + "/mods");
    if (!dir.exists()) {
        return;
    }
    static QRegularExpression subEmety("[-_]"),
        matchName("^(.+?)[-_](?:(?:mc|v)?\\d|(?:fabric))",
                  QRegularExpression::CaseInsensitiveOption);

    QFileInfoList allFiles = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);

    foreach (auto fileData, allFiles) {
        QRegularExpressionMatch match = matchName.match(fileData.fileName());
        if (match.hasMatch()) {
            // qDebug() << match.captured(1);
            QString modName = match.captured(1);
            modName.replace(subEmety, " ");
            func(modName);
        }
    }
}

// void MainWindow::InitFollowerList()
// {
//     connect(ui->followerCombo, &QComboBox::currentIndexChanged, this, [this](int index) {
//         if (index < 0 || index >= ui->followerCombo->count())
//             return;
//         qDebug() << "Debug: " << index;
//         // 设置下拉选择样式，以及禁用已选择下拉选项,同时开始监听文件夹内文件变化
//         if (_comboxDisableCache[1] != -1) {
//             if (_useSameAddress) {
//                 SetComboBoxDataStatus(ui->mainCombo, _comboxDisableCache[1], true);
//                 _mainModel->item(_comboxDisableCache[1])->setForeground(Qt::black);
//             }
//             _followerModel->item(_comboxDisableCache[1])->setForeground(Qt::black);
//             _dirWatcher.removePath(_versions[1][_comboxDisableCache[1]]);
//         }
//         if (_useSameAddress) {
//             SetComboBoxDataStatus(ui->mainCombo, index, false);
//             _mainModel->item(index)->setForeground(Qt::gray);
//         }

//         _followerModel->item(index)->setForeground(Qt::darkGreen);
//         _comboxDisableCache[1] = index;
//         _dirWatcher.addPath(_versions[1][index]);

//         // 初始化manager，清空_followerFilesCache
//         ListItem::Clear(manager);
//         _followerFilesCache.clear();

//         // 清除list，并选择下拉选项时将选择的版本中的mods文件夹中的mod文件处理并添加到list中
//         ui->followerList->clear();
//         GetFileNameToQList(_versions[1].at(index), [this](QString modName) {
//             _followerFilesCache.append(modName);
//             auto [isContain, containPtr] = ListItem::TryGet(manager, modName);
//             if (isContain) {
//                 QListWidgetItem *cloneItem = containPtr->MakeClone();
//                 ui->followerList->addItem(cloneItem);
//                 containPtr->setState(ListItem::same);
//             } else {
//                 QListWidgetItem *item = new QListWidgetItem(modName);
//                 auto listItem = QSharedPointer<ListItem>(new ListItem(item, modName));
//                 listItem->setState(ListItem::extra);
//                 ui->followerList->addItem(item);
//                 manager.append(listItem);
//             }
//             // qDebug() << ((ListItem) manager.at(0) == (ListItem) manager.at(0));
//         });

//         // 将state为_default的item设置state为non_same
//         for (auto item : manager) {
//             if (item->getState() == ListItem::_default) {
//                 item->setState(ListItem::non_same);
//             }
//         }

//         // qDebug() << manager.size();
//     });
// }
