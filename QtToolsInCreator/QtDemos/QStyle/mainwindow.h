#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QToolBar>
#include <QPushButton>
#include <QCheckBox>
#include <QStyle>
#include <QStringListModel>

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
    void init();

    void initListView();

    void initTreeView();

    void initTableView();

    void initStyle();

    void connectSlots();

private:
    Ui::MainWindow *ui;

    QStringListModel* strModel = nullptr;
};
#endif // MAINWINDOW_H
