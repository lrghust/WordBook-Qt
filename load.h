#ifndef LOAD_H
#define LOAD_H

#include <QWidget>
#include <QMessageBox>
#include <QString>
#include <QFileDialog>

namespace Ui {
class Load;
}

class Load : public QWidget
{
    Q_OBJECT

public:
    explicit Load(QWidget *parent = 0);
    ~Load();

    static double ct1;
    static double ct2;
    static double ct3;
    static bool flag_resume;

private slots:
    void on_ok_clicked();

    void on_search_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_save_clicked();

private:
    Ui::Load *ui;
    QString path;
    QString bakpath;
    QString savepath;
    QString word;
    double t1;
    double t2;
    double t3;
    int c1;
    int c2;
    int c3;
    int flag_path=0;

};

#endif // LOAD_H
