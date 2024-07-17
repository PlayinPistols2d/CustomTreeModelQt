#ifndef CUSTOMTREEVIEW_H
#define CUSTOMTREEVIEW_H

#include <QTreeView>
#include <QItemSelectionModel>

class CustomTreeView : public QTreeView {
    Q_OBJECT

public:
    explicit CustomTreeView(QWidget *parent = nullptr);
    void clearTreeView();

private slots:
    void onItemClicked(const QModelIndex &index);

private:
    void highlightItemAndRelated(const QModelIndex &index);
    void highlightItem(const QModelIndex &index);
    void highlightParents(const QModelIndex &index);
    void highlightChildren(const QModelIndex &parentIndex);
    void highlightSiblings(const QModelIndex &index);
};

#endif // CUSTOMTREEVIEW_H
