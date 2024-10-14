#ifndef COMBOITEMMANAGER_H
#define COMBOITEMMANAGER_H

#include <QComboBox>
#include <QStandardItemModel>
#include <QStringList>

class ComboItemManager
{
public:
    enum Index { main, follower };
    enum State { normal, onSelected, disabled };

public:
    ComboItemManager(QComboBox *main, QComboBox *follower);
    ~ComboItemManager();

    void SetState(const Index &i, const State &st, const int &itemIndex);
    void SetNormal(const Index &i);
    void SetNormal(const Index &i, const int &index);

    void SetModel(const Index &i, QStandardItemModel *model);

    void AddVersion(const Index &i, const QString &sg);
    const QString &GetVersion(const Index &i, const int &index);
    void ClearVersion(const Index &i);
    const qsizetype GetVersionCount(const Index &i);

    const bool HasStateChanged(const Index &i) const;
    const int &GetIndexCache(const Index &i) const;

private:
    QComboBox *m_mainCombo;
    QComboBox *m_followerCombo;

    QStringList m_mainVersions;
    QStringList m_followerVersions;
    int m_mainIndexCache = -1, m_followerIndexCache = -1;
    QStandardItemModel *m_mainModel;
    QStandardItemModel *m_followerModel;

    QComboBox &GetCombo(const Index &i);
    QStringList &GetStringList(const Index &i);
    QStandardItemModel &GetModel(const Index &i);
};

#endif // COMBOITEMMANAGER_H
