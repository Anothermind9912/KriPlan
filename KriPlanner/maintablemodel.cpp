#include "maintablemodel.h"

mainTableModel::mainTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{}

QVariant mainTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return "Название";
        case 1: return "Тип работы";
        case 2: return "Приоритет";
        case 3: return "Дедлайн";
        case 4: return "Статус работы";
        case 5: return "Статус оплаты";

        }
    }
    return QString::number(section + 1);
}

bool mainTableModel::setHeaderData(int section,
                                   Qt::Orientation orientation,
                                   const QVariant &value,
                                   int role)
{
    if (value != headerData(section, orientation, role)) {
        // FIXME: Implement me!
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}

int mainTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return main_tasks.size();
}

int mainTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 6;
}

bool mainTableModel::hasChildren(const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

bool mainTableModel::canFetchMore(const QModelIndex &parent) const
{
    // FIXME: Implement me!
    return false;
}

void mainTableModel::fetchMore(const QModelIndex &parent)
{
    // FIXME: Implement me!
}

QVariant mainTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const Task &task = main_tasks[index.row()];

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0: return task.title;
        case 1: return task.type;
        case 2: return task.priority;
        case 3: return task.deadline.toString("dd.MM.yyyy");
        case 4: return task.statuswork;
        case 5: return task.statusPay;
        }
    }

    if (role == Qt::ForegroundRole) {
        if (task.statuswork == statusWork::NotStarted)
            return QColor(Qt::gray);

        if (task.statuswork == statusWork::InDevelopment)
            return QColor(Qt::yellow);

        if (task.statuswork == statusWork::Finished)
            return QColor(Qt::green);
    }

    return QVariant();
}

bool mainTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::EditRole)
        return false;

    Task &task = main_tasks[index.row()];

    switch (index.column()) {
    case 0: task.title = value.toString(); break;
    case 2: task.priority = value.toInt(); break;
    default: return false;
    }

    emit dataChanged(index, index, {role});
    return true;
}

Qt::ItemFlags mainTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

bool mainTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if (row < 0 || row > main_tasks.size())
        return false;

    beginInsertRows(parent, row, row + count - 1);

    for (int i = 0; i < count; ++i) {
        Task newTask;
        newTask.id = main_tasks.size() + 1;
        newTask.title = "Новая задача";
        main_tasks.insert(row + i, newTask);
    }

    endInsertRows();
    return true;
}

bool mainTableModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endInsertColumns();
    return true;
}

bool mainTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (row < 0 || row + count > main_tasks.size())
        return false;

    beginRemoveRows(parent, row, row + count - 1);

    for (int i = 0; i < count; ++i) {
        main_tasks.removeAt(row);
    }

    endRemoveRows();
    return true;
}

bool mainTableModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    beginRemoveColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endRemoveColumns();
    return true;
}
