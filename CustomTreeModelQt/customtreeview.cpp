#include "customtreeview.h"
#include "customtreemodel.h"

CustomTreeView::CustomTreeView(QWidget *parent)
    : QTreeView(parent) {
    connect(this, &QTreeView::clicked, this, &CustomTreeView::onItemClicked);
}

void CustomTreeView::clearTreeView() {
    if (auto *model = static_cast<CustomTreeModel*>(this->model())) {
        model->clearModel();
        clearSelection();
    }
}

void CustomTreeView::onItemClicked(const QModelIndex &index) {
    highlightItemAndRelated(index);
}

void CustomTreeView::highlightItemAndRelated(const QModelIndex &index) {
    clearSelection();
    highlightItem(index);
    highlightParents(index);
    highlightChildren(index);
    highlightSiblings(index);
}

void CustomTreeView::highlightItem(const QModelIndex &index) {
    selectionModel()->select(index, QItemSelectionModel::Select);
}

void CustomTreeView::highlightParents(const QModelIndex &index) {
    if (auto *model = static_cast<CustomTreeModel*>(this->model())) {
        QModelIndex parentIndex = model->parent(index);
        while (parentIndex.isValid()) {
            highlightItem(parentIndex);
            parentIndex = model->parent(parentIndex);
        }
    }
}

void CustomTreeView::highlightChildren(const QModelIndex &parentIndex) {
    if (auto *model = static_cast<CustomTreeModel*>(this->model())) {
        int rowCount = model->rowCount(parentIndex);
        for (int row = 0; row < rowCount; ++row) {
            QModelIndex childIndex = model->index(row, 0, parentIndex);
            highlightItem(childIndex);
            highlightChildren(childIndex);
        }
    }
}

void CustomTreeView::highlightSiblings(const QModelIndex &index) {
    if (auto *model = static_cast<CustomTreeModel*>(this->model())) {
        QModelIndex parentIndex = model->parent(index);
        if (parentIndex.isValid()) {
            int siblingCount = model->rowCount(parentIndex);
            for (int row = 0; row < siblingCount; ++row) {
                QModelIndex siblingIndex = model->index(row, 0, parentIndex);
                if (siblingIndex != index) {
                    highlightItem(siblingIndex);
                    highlightChildren(siblingIndex);
                }
            }
        }
    }
}
