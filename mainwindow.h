#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "judger.h"

class Judger;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Judger* Human_Judger;

public slots:
    void GetFile();

signals:
    void OpenJudger();

private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
