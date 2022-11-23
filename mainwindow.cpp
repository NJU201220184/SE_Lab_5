#include "mainwindow.h"
#include "judger.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

class Judger;
class Answer_Repo;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800, 600);
    Human_Judger = new Judger();
    Answer = new Answer_Repo();

    QFile Equal_File("D:\\SE_Lab5\\Human_Judger\\Output\\Equal.csv");
    QFile InEqual_File("D:\\SE_Lab5\\Human_Judger\\Output\\InEqual.csv");
    Equal_File.open( QIODevice::ReadWrite | QIODevice::Truncate);
    InEqual_File.open( QIODevice::ReadWrite | QIODevice::Truncate);
    QTextStream equal_out(&Equal_File);
    QTextStream inequal_out(&InEqual_File);
    equal_out<<"file1, file2\n";
    inequal_out<<"file1, file2\n";
    Equal_File.close();
    InEqual_File.close();

    connect(ui->QuitButton, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->CommitButtom, &QPushButton::clicked, this, &MainWindow::GetFile);
    connect(this, &MainWindow::OpenJudger, Human_Judger, &Judger::ShowData);
    connect(Human_Judger, &Judger::OpenAnswerRepo, Answer, &Answer_Repo::getRecommendation);
    connect(Answer, &Answer_Repo::Recommendation, this, &MainWindow::OpenRecommendation);
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

    ui->Path_A->setText("");
    ui->Path_B->setText("");

    emit OpenJudger();
    this->close();
}

void MainWindow::OpenRecommendation(QString file_A, QString file_B, QString relation)
{
    ui->Path_A->setText(file_A);
    ui->Path_B->setText(file_B);
    ui->Recommendation->setText(relation);
    this->show();
}



