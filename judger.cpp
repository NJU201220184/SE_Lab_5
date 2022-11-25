#include "judger.h"
#include "ui_judger.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTextCharFormat>

Judger::Judger(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Judger)
{
    ui->setupUi(this);
    this->setWindowTitle("Human Judger");
    this->setFixedSize(1800, 800);
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
    qDebug()<<"Show data";

    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPointSize(12);

    ui->File_A_Code->setFont(font);
    ui->File_B_Code->setFont(font);

    ui->File_A_Name->setText(File_A);
    QFile FileA(File_A);
    ui->File_B_Name->setText(File_B);
    QFile FileB(File_B);

    if (FileA.open(QIODevice::ReadOnly | QIODevice::Text) && FileB.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (true)
        {

            if (!FileA.atEnd() && !FileB.atEnd())
            {
                //qDebug()<<"Both lines are:";
                QString strA = FileA.readLine();
                QString strB = FileB.readLine();

                //qDebug()<<strA;
                //qDebug()<<strB;
                if(strA == strB)
                {
                    code_A += strA;
                    code_B += strB;
                }
                else {
                    code_A += "$\t";
                    code_B += "$\t";
                    code_A += strA;
                    code_B += strB;
                }
            }

            else if(!FileA.atEnd())
            {
                QByteArray line_A = FileA.readLine();
                QString strA(line_A);
                code_A += "+\t";
                code_B += "-\t";
                code_B += "\n";
                code_A += strA;
            }

            else if(!FileB.atEnd())
            {
                QByteArray line_B = FileA.readLine();
                QString strB(line_B);
                code_A += "-\t";
                code_A += "\n";
                code_B += "+\t";
                code_B += strB;
            }

            else if (FileA.atEnd() && FileB.atEnd())
            {
                break;
            }
        }
    }

    //qDebug()<<code_A;
    //qDebug()<<code_B;

    ui->File_A_Code->setText(code_A);
    ui->File_B_Code->setText(code_B);

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

