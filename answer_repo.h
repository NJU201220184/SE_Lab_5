#ifndef ANSWER_REPO_H
#define ANSWER_REPO_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class Answer_Repo;
}

class Answer_Repo : public QWidget
{
    Q_OBJECT

public:
    Answer_Repo(QWidget *parent = nullptr);
    ~Answer_Repo();

signals:
    void Recommendation(QString, QString, QString);

public slots:
    void getRecommendation(QString, QString, QString);
    void sendRecommendation();

private:
    Ui::Answer_Repo *ui;
    QString file_A;
    QString file_B;
};

#endif // ANSWER_REPO_H
