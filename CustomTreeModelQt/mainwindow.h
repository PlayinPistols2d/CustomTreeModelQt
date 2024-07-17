#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "customtreemodel.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CustomTreeModel *treeModel = nullptr;
    void showcase();
};
#endif // MAINWINDOW_H
