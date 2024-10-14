#include "listitem.h"

QListWidgetItem *ListItem::MakeClone()
{
    if (m_hasClone) {
        qDebug() << "Another Clone Error: Already has a clone." << name;
        throw "Another Clone Error: Already has a clone.";
    }
    if (item != nullptr) {
        m_clone = item->clone();
        m_hasClone = true;
        setColorByState(*m_clone);
        return m_clone;
    }
    qDebug() << "None Item Error: Nothing to clone.";
    throw "None Item Error: Nothing to clone.";
}

const bool ListItem::hasClone() const
{
    return m_hasClone;
}

const ListItem::State &ListItem::getState() const
{
    return m_state;
}

void ListItem::setState(State newState)
{
    m_state = newState;
    setColorByState(*item);
    if (m_hasClone)
        setColorByState(*m_clone);
}

void ListItem::Reset()
{
    // qDebug() << "debug check m_hasClone: " << m_hasClone;
    if (m_hasClone) {
        // qDebug() << "debug clear m_clone. ";
        m_hasClone = false;
        m_clone->listWidget()->removeItemWidget(m_clone);
        m_clone = Q_NULLPTR;
    }
    // qDebug() << "debug reset m_state to _default. ";
    m_state = _default;
    qDebug() << name;
    if (item)
        setColorByState(*item);
}

void ListItem::setColorByState(QListWidgetItem &item)
{
    switch (m_state) {
    case same:
        item.setBackground(Qt::green);
        break;
    case non_same:
        item.setBackground(Qt::gray);
        break;
    case extra:
        item.setBackground(Qt::cyan);
        break;
    default:
        item.setBackground(Qt::white);
        break;
    }
}
