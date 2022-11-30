#include "answer_repo.h"
#include "ui_answer_repo.h"
#include "mainwindow.h"
#include <QFile>
#include <QFileDevice>
#include <QDebug>
#include <QVector>

Answer_Repo::Answer_Repo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Answer_Repo)
{
    ui->setupUi(this);
    this->setFixedSize(900, 600);
    connect(ui->Continue, &QPushButton::clicked, this, &Answer_Repo::sendRecommendation);
    connect(ui->Quit, &QPushButton::clicked, this, &Answer_Repo::close);
}

Answer_Repo::~Answer_Repo()
{
    delete ui;
}

void Answer_Repo::getRecommendation(QString File_A, QString File_B, QString judgement)
{
    bool Find = false;
    QVector<QString> file_A_list;
    QVector<QString> file_B_list;
    if(judgement == "Equal")
    {
        qDebug()<<File_A<<": "<<File_B;
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
                    qDebug()<<file_A<<": "<<file_B;
                    if((file_A == File_A && file_B != File_B))
                    {
                        file_A_list.push_back(file_B);
                        file_B_list.push_back(File_B);
                    }
                    else if((file_A == File_B && file_B != File_A))
                    {
                        file_A_list.push_back(file_B);
                        file_B_list.push_back(File_A);
                    }
                    else if(file_A != File_A && file_B == File_B)
                    {
                        file_A_list.push_back(file_A);
                        file_B_list.push_back(File_A);
                    }
                    else if(file_A != File_B && file_B == File_A)
                    {
                        file_A_list.push_back(file_A);
                        file_B_list.push_back(File_B);
                    }
                }
            }
        }
        Equal_File.close();

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
                    qDebug()<<file_A<<": "<<file_B;
                    for(int i = 0; i < file_A_list.size(); i++)
                    {
                        if((file_A_list[i] == file_A && file_B_list[i] == file_B) || (file_A_list[i] == file_B && file_B_list[i] == file_A))
                        {
                            file_A_list.erase(file_A_list.begin() + i);
                            file_B_list.erase(file_B_list.begin() + i);
                        }
                    }
                }
            }
        }
        Equal_File.close();

        if(!file_A_list.empty())
        {
            Find = true;
            ui->Recommendation_A->setText(file_A_list[0]);
            ui->Recommendation_B->setText(file_B_list[0]);
            ui->Relation->setText("Equal");
        }

        if(Find)
        {
            this->show();
            return;
        }

        file_A_list.clear();
        file_B_list.clear();

        QFile InEqual_File("D:\\SE_Lab5\\Human_Judger\\Output\\InEqual.csv");
        if(InEqual_File.open( QIODevice::ReadOnly| QIODevice::Text))
        {
            while(!InEqual_File.atEnd())
            {
                QByteArray line = InEqual_File.readLine();
                QString str(line);
                if(str.indexOf("file1") != -1)
                {
                    qDebug()<<"Not a pair";
                }
                else{
                    int index = str.indexOf(",");
                    QString file_A = str.left(index);
                    QString file_B = str.mid(index + 1, str.size() - index - 2);
                    if(file_A == File_A)
                    {
                        file_A_list.push_back(file_B);
                        file_B_list.push_back(File_B);
                    }
                    else if(file_A == File_B)
                    {
                        file_A_list.push_back(file_B);
                        file_B_list.push_back(File_A);

                    }
                    else if(file_B == File_B)
                    {
                        file_A_list.push_back(file_A);
                        file_B_list.push_back(File_A);
                    }
                    else if(file_B == File_A)
                    {
                        file_A_list.push_back(file_A);
                        file_B_list.push_back(File_B);
                    }
                }
            }
        }
        InEqual_File.close();

        if(InEqual_File.open( QIODevice::ReadOnly| QIODevice::Text))
        {
            while(!InEqual_File.atEnd())
            {
                QByteArray line = InEqual_File.readLine();
                QString str(line);
                if(str.indexOf("file1") != -1)
                {
                    qDebug()<<"Not a pair";
                }
                else{
                    int index = str.indexOf(",");
                    QString file_A = str.left(index);
                    QString file_B = str.mid(index + 1, str.size() - index - 2);
                    for(int i = 0; i < file_A_list.size(); i++)
                    {
                        if((file_A_list[i] == file_A && file_B_list[i] == file_B) || (file_A_list[i] == file_B && file_B_list[i] == file_A))
                        {
                            file_A_list.erase(file_A_list.begin() + i);
                            file_B_list.erase(file_B_list.begin() + i);
                        }
                    }
                }
            }
        }
        InEqual_File.close();

        if(!file_A_list.empty())
        {
            Find = true;
            ui->Recommendation_A->setText(file_A_list[0]);
            ui->Recommendation_B->setText(file_B_list[0]);
            ui->Relation->setText("InEqual");
        }

        if(Find)
        {
            this->show();
            return;
        }


        if(!Find)
        {
            ui->Recommendation_A->setText("");
            ui->Recommendation_B->setText("");
            ui->Relation->setText("No Recommendation");
            this->show();
            return;
        }
    }

    else if(judgement == "InEqual")
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
                else{
                    int index = str.indexOf(",");
                    QString file_A = str.left(index);
                    QString file_B = str.mid(index + 1, str.size() - index - 2);
                    if(file_A == File_A)
                    {
                        file_A_list.push_back(file_B);
                        file_B_list.push_back(File_B);
                    }
                    else if(file_A == File_B)
                    {
                        file_A_list.push_back(file_B);
                        file_B_list.push_back(File_A);

                    }
                    else if(file_B == File_B)
                    {
                        file_A_list.push_back(file_A);
                        file_B_list.push_back(File_A);
                    }
                    else if(file_B == File_A)
                    {
                        file_A_list.push_back(file_A);
                        file_B_list.push_back(File_B);
                    }
                }
            }
        }
        Equal_File.close();

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
                else{
                    int index = str.indexOf(",");
                    QString file_A = str.left(index);
                    QString file_B = str.mid(index + 1, str.size() - index - 2);
                    for(int i = 0; i < file_A_list.size(); i++)
                    {
                        if((file_A_list[i] == file_A && file_B_list[i] == file_B) || (file_A_list[i] == file_B && file_B_list[i] == file_A))
                        {
                            file_A_list.erase(file_A_list.begin() + i);
                            file_B_list.erase(file_B_list.begin() + i);
                        }
                    }
                }
            }
        }
        Equal_File.close();

        if(!file_A_list.empty())
        {
            Find = true;
            ui->Recommendation_A->setText(file_A_list[0]);
            ui->Recommendation_B->setText(file_B_list[0]);
            ui->Relation->setText("InEqual");
        }

        if(Find)
        {
            this->show();
            return;
        }


        if(!Find)
        {
            ui->Recommendation_A->setText("");
            ui->Recommendation_B->setText("");
            ui->Relation->setText("No Recommendation");
            this->show();
            return;
        }
    }
}

void Answer_Repo::sendRecommendation()
{
    QString file_A = ui->Recommendation_A->text();
    QString file_B = ui->Recommendation_B->text();
    QString relation = ui->Relation->text();
    emit Recommendation(file_A, file_B, relation);
    this->close();
}
