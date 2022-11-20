#include "mainwindow.h"
#include "judger.h"
#include "ui_mainwindow.h"
#include <QDebug>

class Judger;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Human_Judger = new Judger();
    connect(ui->QuitButton, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->CommitButtom, &QPushButton::clicked, this, &MainWindow::GetFile);
    connect(this, &MainWindow::OpenJudger, Human_Judger, &Judger::ShowData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::GetFile()
{
    QString file_Path_A = ui->Path_A->text();
    QString file_Path_B = ui->Path_B->text();

    Human_Judger->File_A = file_Path_A;
    Human_Judger->File_B = file_Path_B;
    qDebug()<<file_Path_A;
    qDebug()<<file_Path_B;
    emit OpenJudger();
}





