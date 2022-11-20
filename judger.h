#ifndef JUDGER_H
#define JUDGER_H

#include <QWidget>
#include <QString>

#include "mainwindow.h"

namespace Ui {
class Judger;
}

class Judger : public QWidget
{
    Q_OBJECT

public:
    Judger(QWidget *parent = nullptr);
    ~Judger();
    QString File_A;
    QString File_B;

public slots:
    void ShowData();

private:
    Ui::Judger *ui;
    QString code_A;
    QString code_B;
};

#endif // JUDGER_H
