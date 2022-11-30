#include "table.h"
#include "ui_table.h"
#include <QFile>
#include <QDebug>

Table::Table(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Table)
{
    ui->setupUi(this);
    connect(ui->Equal, &QPushButton::clicked, this, &Table::ShowEqualPairs);
    connect(ui->InEqual, &QPushButton::clicked, this, &Table::ShowInEqualPairs);
    connect(ui->Quit, &QPushButton::clicked, this, &Table::close);
}

Table::~Table()
{
    delete ui;
}

void Table::ShowEqualPairs()
{
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPointSize(10);
    ui->Pairs->setFont(font);

    QFile Equal_File("D:\\SE_Lab5\\Human_Judger\\Output\\Equal.csv");
    QString Equal_List = "";
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
                Equal_List += str;
                Equal_List += '\n';
            }
        }
    }

    Equal_File.close();
    ui->Pairs->setText(Equal_List);
    this->show();
}

void Table::ShowInEqualPairs()
{
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPointSize(10);
    ui->Pairs->setFont(font);

    QFile InEqual_File("D:\\SE_Lab5\\Human_Judger\\Output\\InEqual.csv");
    QString InEqual_List = "";
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
            else
            {
                InEqual_List += str;
                InEqual_List += '\n';
            }
        }
    }

    InEqual_File.close();
    ui->Pairs->setText(InEqual_List);
    this->show();
}
