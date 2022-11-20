#include "judger.h"
#include "ui_judger.h"

#include <QFileDialog>
#include <QFile>

Judger::Judger(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Judger)
{
    ui->setupUi(this);
}

Judger::~Judger()
{
    delete ui;
}

void Judger::ShowData()
{
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

