#include "judger.h"
#include "ui_judger.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>

Judger::Judger(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Judger)
{
    ui->setupUi(this);
    this->setWindowTitle("Human Judger");
    this->setFixedSize(1400, 800);
    connect(ui->Quit, &QPushButton::clicked, this, &Judger::close);
    connect(ui->Check, &QPushButton::clicked, this, &Judger::Check);
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
    code_A = "";
    code_B = "";
    font.setFamily("Microsoft YaHei");
    font.setPointSize(12);

    ui->File_A_Code->setFont(font);
    ui->File_B_Code->setFont(font);

    ui->File_A_Name->setText(File_A);
    QFile FileA(File_A);
    ui->File_B_Name->setText(File_B);
    QFile FileB(File_B);

    QVector<QString> File_A_Code;
    QVector<QString> File_B_Code;

    if (FileA.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!FileA.atEnd())
        {
            QByteArray line = FileA.readLine();
            QString str(line);
            File_A_Code.push_back(str);
        }
        FileA.close();
    }

    if (FileB.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!FileB.atEnd())
        {
            QByteArray line = FileB.readLine();
            QString str(line);
            File_B_Code.push_back(str);
        }
        FileB.close();
    }

    if(File_A_Code.size() >= File_B_Code.size())
    {
        int i = 0;
        for(i; i < File_B_Code.size(); ++i)
        {
            if(File_A_Code[i] == File_B_Code[i])
            {
                code_A += File_A_Code[i];
                code_B += File_B_Code[i];
            }
            else {
                code_A += "$\t";
                code_B += "$\t";
                code_A += File_A_Code[i];
                code_B += File_B_Code[i];
            }
        }
        for(i; i < File_A_Code.size(); ++i)
        {
            code_A += "+\t";
            code_B += "-\t";
            code_A += File_A_Code[i];
            code_B += "\n";
        }
    }

    else
    {
        int i = 0;
        for(i; i < File_A_Code.size(); ++i)
        {
            if(File_A_Code[i] == File_B_Code[i])
            {
                code_A += File_A_Code[i];
                code_B += File_B_Code[i];
            }
            else {
                code_A += "$\t";
                code_B += "$\t";
                code_A += File_A_Code[i];
                code_B += File_B_Code[i];
            }
        }
        for(i; i < File_B_Code.size(); ++i)
        {
            code_A += "-\t";
            code_B += "+\t";
            code_B += File_B_Code[i];
            code_A += "\n";
        }
    }

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

void Judger::Check()
{
    if(judgement == "Equal")
    {
        QFile Equal_File("D:\\SE_Lab5\\Human_Judger\\Output\\Equal.csv");
        if(Equal_File.open( QIODevice::ReadOnly| QIODevice::Text))
        {
            while(!Equal_File.atEnd())
            {
                QByteArray line = Equal_File.readLine();
                QString str(line);
                if(str.indexOf("file1") != -1)
                {
                    qDebug()<<"Not a pair";
                }
                else
                {
                    int index = str.indexOf(",");
                    QString file_A = str.left(index);
                    QString file_B = str.mid(index + 1, str.size() - index - 2);
                    qDebug()<<(file_A == File_A)<<":"<<(file_B == File_B);
                    if((file_A == File_A && file_B == File_B) || (file_A == File_B && file_B == File_A))
                    {
                        QMessageBox::information(NULL, "Repeated", "You have already judged this before...");
                        Equal_File.close();
                        ui->lineEdit->setText("");
                        this->close();
                        emit OpenMainWindow();
                        return;
                    }
                }
            }
        }
        QMessageBox::information(NULL, "OK", "This pair hasn't been judged yet...");
        Equal_File.close();
    }
}
