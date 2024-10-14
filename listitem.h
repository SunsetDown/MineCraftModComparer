#ifndef LISTITEM_H
#define LISTITEM_H

#include <QListWidgetItem>

struct ListItem
{
    ListItem() {}
    ListItem(QListWidgetItem *item, const QString &name)
        : item(item)
        , name(name)
    {}

    ListItem(const ListItem &other)
        : item(other.item)
        , name(other.name)
        , m_hasClone(other.m_hasClone)
        , m_clone(other.m_clone)
    {
        // qDebug() << "List Item Copy";
    }

    ListItem &operator=(const ListItem &other)
    {
        // qDebug() << "List Item Assignment";
        if (this != &other) {
            item = other.item;
            name = other.name;
            m_hasClone = other.m_hasClone;
            if (m_hasClone)
                m_clone = other.m_clone;
        }
        return *this;
    }

    // ~ListItem() { qDebug() << "List Item Destroy." << name; }

    enum State { _default = -1, same, non_same, extra };
    QListWidgetItem *item;
    QString name;
    QListWidgetItem *MakeClone();

    const bool hasClone() const;

    const State &getState() const;
    void setState(State newState);

    void Reset();

    bool operator==(const QString &other) const
    {
        return !QString::compare(name, other, Qt::CaseInsensitive);
    }

    bool operator!=(const QString &other) const { return !(name == other); }

    bool operator==(const ListItem &other) const
    {
        return !QString::compare(name, other.name, Qt::CaseInsensitive);
    }

    bool operator!=(const ListItem &other) const { return !(*this == other); }

    static std::tuple<bool, QSharedPointer<ListItem>> TryGet(QList<QSharedPointer<ListItem>> &list,
                                                             const QString &target)
    {
        for (auto &item : list) {
            if (*item == target)
                return {true, item};
        }
        return {false, nullptr};
    }

    static void Clear(QList<QSharedPointer<ListItem>> &list)
    {
        // qDebug() << "start clear. list size:" << list.size();
        for (int i = 0; i < list.size();) {
            auto item = list[i];
            if (item->m_state == same) {
                item->Reset();
                // qDebug() << item->name << "reset.";
            } else if (item->m_state == extra) {
                list.removeAt(i);
                continue;
            }
            i++;
        }
        // qDebug() << "clear done. cleared size: " << list.size();
    }

private:
    State m_state = _default;
    QListWidgetItem *m_clone;
    bool m_hasClone = false;

    void setColorByState(QListWidgetItem &item);
};

#endif // LISTITEM_H
