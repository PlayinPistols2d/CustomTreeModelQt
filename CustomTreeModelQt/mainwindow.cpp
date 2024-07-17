#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showcase();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showcase()
{
    setWindowTitle("CustomTreeModel example");

    QModelIndex localparentIndex;
    QModelIndex localchildIndex;
    treeModel = new CustomTreeModel(this);

    treeModel->addParentItem("Parent item 1");
    localparentIndex = treeModel->index(0, 0, QModelIndex());
    treeModel->addChildItem(localparentIndex, "Child item 1-1");
    treeModel->addChildItem(localparentIndex, "Child item 1-2");

    treeModel->addParentItem("Parent item 2");

    treeModel->addParentItem("Parent item 3");
    localparentIndex = treeModel->index(2, 0, QModelIndex());
    treeModel->addChildItem(localparentIndex, "Child item 3-1");

    treeModel->addParentItem("Parent item 4");
    localparentIndex = treeModel->index(3, 0, QModelIndex());
    treeModel->addChildItem(localparentIndex, "Child item 4-1");
    localchildIndex = treeModel->index(0, 0, localparentIndex);
    treeModel->addChildItem(localchildIndex, "Child of Child 1 of Parent 4");

    ui->treeView->setModel(treeModel);
    ui->treeView->setHeaderHidden(true);
    ui->treeView->show();
}

