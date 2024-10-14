#include "comboitemmanager.h"
#define DISABLE_COMBO_DATA QVariant(0)
#define ENABLE_COMBO_DATA QVariant(33)

static void SetComboBoxDataStatus(QComboBox &cb, int index, bool status)
{
    if (status)
        cb.setItemData(index, ENABLE_COMBO_DATA, Qt::UserRole - 1);
    else
        cb.setItemData(index, DISABLE_COMBO_DATA, Qt::UserRole - 1);
}

static Qt::GlobalColor GetColor(const ComboItemManager::State &i)
{
    switch (i) {
    case ComboItemManager::normal:
        return Qt::black;
    case ComboItemManager::disabled:
        return Qt::gray;
    case ComboItemManager::onSelected:
        return Qt::darkGreen;
    default:
        return Qt::black;
    }
}

ComboItemManager::ComboItemManager(QComboBox *main, QComboBox *follower)
    : m_mainCombo(main)
    , m_followerCombo(follower)
{}

ComboItemManager::~ComboItemManager()
{
    delete m_mainModel;
    delete m_followerModel;
}

void ComboItemManager::SetState(const Index &i, const State &st, const int &itemIndex)
{
    GetModel(i).item(itemIndex)->setForeground(GetColor(st));
    if (st == disabled) {
        SetComboBoxDataStatus(GetCombo(i), itemIndex, false);
        return;
    }
    if (i == main)
        m_mainIndexCache = itemIndex;
    else
        m_followerIndexCache = itemIndex;
}

void ComboItemManager::SetNormal(const Index &i)
{
    int index = i == main ? m_mainIndexCache : m_followerIndexCache;
    GetModel(i).item(index)->setForeground(GetColor(normal));
    SetComboBoxDataStatus(GetCombo(i), index, true);
}

void ComboItemManager::SetNormal(const Index &i, const int &index)
{
    GetModel(i).item(index)->setForeground(GetColor(normal));
    SetComboBoxDataStatus(GetCombo(i), index, true);
}

void ComboItemManager::SetModel(const Index &i, QStandardItemModel *model)
{
    if (i == main)
        m_mainModel = model;
    else
        m_followerModel = model;
}

// version

void ComboItemManager::AddVersion(const Index &i, const QString &sg)
{
    GetStringList(i).append(sg);
}

const QString &ComboItemManager::GetVersion(const Index &i, const int &index)
{
    return GetStringList(i)[index];
}

void ComboItemManager::ClearVersion(const Index &i)
{
    GetStringList(i).clear();
    if (i == main)
        m_mainIndexCache = -1;
    else
        m_followerIndexCache = -1;
}

const qsizetype ComboItemManager::GetVersionCount(const Index &i)
{
    return GetStringList(i).count();
}

// index cache

const int &ComboItemManager::GetIndexCache(const Index &i) const
{
    return i == main ? m_mainIndexCache : m_followerIndexCache;
}

const bool ComboItemManager::HasStateChanged(const Index &i) const
{
    if (i == main) {
        return m_mainIndexCache != -1;
    }
    return m_followerIndexCache != -1;
}

// Index translator

QComboBox &ComboItemManager::GetCombo(const Index &i)
{
    return i == main ? *m_mainCombo : *m_followerCombo;
}
QStringList &ComboItemManager::GetStringList(const Index &i)
{
    return i == main ? m_mainVersions : m_followerVersions;
}
QStandardItemModel &ComboItemManager::GetModel(const Index &i)
{
    return i == main ? *m_mainModel : *m_followerModel;
}
