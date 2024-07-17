#ifndef CUSTOMTREEMODEL_H
#define CUSTOMTREEMODEL_H

#include <QAbstractItemModel>
#include <QList>
#include <QVariant>

class CustomTreeModel : public QAbstractItemModel {
    Q_OBJECT

public:
    explicit CustomTreeModel(QObject *parent = nullptr);
    ~CustomTreeModel();

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    void addParentItem(const QVariant &data);
    void addChildItem(const QModelIndex &parent, const QVariant &data);
    void clearModel();

private:
    struct TreeItem {
        explicit TreeItem(const QVariant &data, TreeItem *parent = nullptr)
            : m_itemData(data), m_parentItem(parent) {}
        ~TreeItem() { qDeleteAll(m_childItems); }

        void appendChild(TreeItem *child) { m_childItems.append(child); }
        TreeItem *child(int row) const { return m_childItems.value(row); }
        int childCount() const { return m_childItems.count(); }
        QVariant data() const { return m_itemData; }
        int row() const { return m_parentItem ? m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this)) : 0; }
        TreeItem *parentItem() { return m_parentItem; }

        QList<TreeItem*> m_childItems;
        QVariant m_itemData;
        TreeItem *m_parentItem;
    };

    TreeItem* getItem(const QModelIndex &index) const {
        if (index.isValid()) {
            TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
            if (item) return item;
        }
        return rootItem;
    }

    TreeItem *rootItem;
};

#endif // CUSTOMTREEMODEL_H
