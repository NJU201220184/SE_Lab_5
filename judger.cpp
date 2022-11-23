#include "judger.h"
#include "ui_judger.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>

Judger::Judger(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Judger)
{
    ui->setupUi(this);
    this->setWindowTitle("Human Judger");
    this->setFixedSize(1100, 600);
    connect(ui->Quit, &QPushButton::clicked, this, &Judger::close);
    connect(ui->Commit, &QPushButton::clicked, this, &Judger::GetRecommendation);
    connect(ui->Commit, &QPushButton::clicked, this, &Judger::close);
}

Judger::~Judger()
{
    delete ui;
}

void Judger::ShowData()
{
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPointSize(15);
    font.setBold(true);
    ui->File_A_Code->setFont(font);
    ui->File_B_Code->setFont(font);

    ui->File_A_Name->setText(File_A);
    QFile FileA(File_A);
    FileA.open(QIODevice::ReadOnly);
    QByteArray arrA = FileA.readAll();
    ui->File_A_Code->setText(arrA);

    ui->File_B_Name->setText(File_B);
    QFile FileB(File_B);
    FileB.open(QIODevice::ReadOnly);
    QByteArray arrB = FileB.readAll();
    ui->File_B_Code->setText(arrB);

    this->show();
}

void Judger::GetRecommendation()
{
    judgement = ui->lineEdit->text();
    ui->File_A_Name->setText("");
    ui->File_A_Code->setText("");
    ui->File_B_Name->setText("");
    ui->File_B_Code->setText("");
    ui->lineEdit->setText("");
    qDebug()<<judgement;

    if(judgement == "Equal"){
        QFile Equal_File("D:\\SE_Lab5\\Human_Judger\\Output\\Equal.csv");
        Equal_File.open( QIODevice::ReadWrite | QIODevice::Append);
        QTextStream equal_out(&Equal_File);
        equal_out<<File_A<<","<<File_B<<"\n";
        Equal_File.close();
    }

    else if(judgement == "InEqual"){
        QFile InEqual_File("D:\\SE_Lab5\\Human_Judger\\Output\\InEqual.csv");
        InEqual_File.open( QIODevice::ReadWrite | QIODevice::Append);
        QTextStream inequal_out(&InEqual_File);
        inequal_out<<File_A<<","<<File_B<<"\n";
        InEqual_File.close();
    }

    emit OpenAnswerRepo(File_A, File_B, judgement);
}

