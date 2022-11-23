#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "judger.h"
#include "answer_repo.h"

class Judger;
class Answer_Repo;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void GetFile();
    void OpenRecommendation(QString, QString, QString);

signals:
    void OpenJudger();

private:
    Ui::MainWindow *ui;
    Judger* Human_Judger;
    Answer_Repo* Answer;
};
#endif // MAINWINDOW_H
