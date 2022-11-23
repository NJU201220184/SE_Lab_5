#include "answer_repo.h"
#include "ui_answer_repo.h"
#include "mainwindow.h"
#include <QFile>
#include <QFileDevice>
#include <QDebug>

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
                else{
                    int index = str.indexOf(",");
                    QString file_A = str.left(index);
                    QString file_B = str.mid(index + 1, str.size() - index - 2);
                    qDebug()<<file_A<<": "<<file_B;
                    if((file_A == File_A && file_B != File_B))
                    {
                        ui->Recommendation_A->setText(File_B);
                        ui->Recommendation_B->setText(file_B);
                        ui->Relation->setText("Equal");
                        Find = true;
                        break;
                    }
                    else if((file_A == File_B && file_B != File_A))
                    {
                        ui->Recommendation_A->setText(File_A);
                        ui->Recommendation_B->setText(file_B);
                        ui->Relation->setText("Equal");
                        Find = true;
                        break;
                    }
                    else if(file_A != File_A && file_B == File_B)
                    {
                        ui->Recommendation_A->setText(File_A);
                        ui->Recommendation_B->setText(file_A);
                        ui->Relation->setText("Equal");
                        Find = true;
                        break;
                    }
                    else if(file_A != File_B && file_B == File_A)
                    {
                        ui->Recommendation_A->setText(File_B);
                        ui->Recommendation_B->setText(file_A);
                        ui->Relation->setText("Equal");
                        Find = true;
                        break;
                    }
                }
            }
            if(Find)
            {
                this->show();
                return;
            }
        }
        Equal_File.close();

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
                    QString file_B = str.mid(index + 1, str.size() - index - 3);
                    if(file_A == File_A)
                    {
                        ui->Recommendation_A->setText(file_B);
                        ui->Recommendation_B->setText(File_B);
                        ui->Relation->setText("InEqual");
                        Find = true;
                        break;
                    }
                    else if(file_A == File_B)
                    {
                        ui->Recommendation_A->setText(file_B);
                        ui->Recommendation_B->setText(File_A);
                        ui->Relation->setText("InEqual");
                        Find = true;
                        break;
                    }
                    else if(file_B == File_B)
                    {
                        ui->Recommendation_A->setText(file_A);
                        ui->Recommendation_B->setText(File_A);
                        ui->Relation->setText("InEqual");
                        Find = true;
                        break;
                    }
                    else if(file_B == File_A)
                    {
                        ui->Recommendation_A->setText(file_A);
                        ui->Recommendation_B->setText(File_B);
                        ui->Relation->setText("InEqual");
                        Find = true;
                        break;
                    }
                }
            }
            if(Find)
            {
                this->show();
                return;
            }
        }
        InEqual_File.close();

        if(!Find)
        {
            ui->Recommendation_A->setText("No file");
            ui->Recommendation_B->setText("No file");
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
                    QString file_B = str.mid(index + 1, str.size() - index - 3);
                    if(file_A == File_A)
                    {
                        ui->Recommendation_A->setText(File_B);
                        ui->Recommendation_B->setText(file_B);
                        ui->Relation->setText("Equal");
                        Find = true;
                        break;
                    }
                    else if(file_A == File_B)
                    {
                        ui->Recommendation_A->setText(File_A);
                        ui->Recommendation_B->setText(file_B);
                        ui->Relation->setText("Equal");
                        Find = true;
                        break;
                    }
                    else if(file_B == File_B)
                    {
                        ui->Recommendation_A->setText(File_A);
                        ui->Recommendation_B->setText(file_A);
                        ui->Relation->setText("Equal");
                        Find = true;
                        break;
                    }
                    else if(file_B == File_A)
                    {
                        ui->Recommendation_A->setText(File_B);
                        ui->Recommendation_B->setText(file_A);
                        ui->Relation->setText("Equal");
                        Find = true;
                        break;
                    }
                }
            }
            if(Find)
            {
                this->show();
                return;
            }
        }
        Equal_File.close();

        if(!Find)
        {
            ui->Recommendation_A->setText("No file");
            ui->Recommendation_B->setText("No file");
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
