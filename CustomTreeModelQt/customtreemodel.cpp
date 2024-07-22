#include "customtreemodel.h"

CustomTreeModel::CustomTreeModel(QObject *parent)
    : QAbstractItemModel(parent), rootItem(new TreeItem("Root")) {}

CustomTreeModel::~CustomTreeModel() {
    delete rootItem;
}

void CustomTreeModel::addParentItem(const QVariant &data) {
    beginInsertRows(QModelIndex(), rootItem->childCount(), rootItem->childCount());
    rootItem->appendChild(new TreeItem(data, rootItem));
    endInsertRows();
}

void CustomTreeModel::addChildItem(const QModelIndex &parent, const QVariant &data) {
    TreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return;

    int row = parentItem->childCount();
    beginInsertRows(parent, row, row);
    parentItem->appendChild(new TreeItem(data, parentItem));
    endInsertRows();
}

void CustomTreeModel::removeParentItem(const QModelIndex &parent)
{
    if (!parent.isValid())
        return;

    TreeItem *parentItem = getItem(parent);
    if (!parentItem || parentItem == rootItem)
        return;

    int row = parentItem->row();
    beginRemoveRows(parent.parent(), row, row);

    parentItem->parentItem()->m_childItems.removeAt(row);

    delete parentItem;

    endRemoveRows();
}

QVariant CustomTreeModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    return item->data();
}

Qt::ItemFlags CustomTreeModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}

QVariant CustomTreeModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return QVariant("Tree View"); // could be adjusted for your needs or extracted as function
    }

    return QVariant();
}

QModelIndex CustomTreeModel::index(int row, int column, const QModelIndex &parent) const {
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex CustomTreeModel::parent(const QModelIndex &index) const {
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int CustomTreeModel::rowCount(const QModelIndex &parent) const {
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int CustomTreeModel::columnCount(const QModelIndex &parent) const {
    return 1;
}

void CustomTreeModel::clearModel() {
    if (rootItem->childCount() > 0) {
        rootItem->m_childItems.clear();
        rootItem->m_itemData.clear();
    }
    emit layoutChanged();
}
