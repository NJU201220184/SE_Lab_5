#ifndef JUDGER_H
#define JUDGER_H

#include <QWidget>
#include <QString>

#include "mainwindow.h"
#include "answer_repo.h"

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
    void Check();
    void GetRecommendation();

signals:
    void OpenAnswerRepo(QString, QString, QString);
    void OpenMainWindow();


private:
    Ui::Judger *ui;
    QString code_A;
    QString code_B;
    QString judgement;
};

#endif // JUDGER_H
