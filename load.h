#ifndef LOAD_H
#define LOAD_H

#include <QWidget>
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include "WordBook.h"

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
    static QString traverse_text;

private slots:
    void on_ok_clicked();

    void on_search_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_save_clicked();

    void on_unsort_toggled(bool checked);

    void on_sort_toggled(bool checked);

    void on_hash_toggled(bool checked);

    void on_traverse_clicked();

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
    int flag_traverse=0;

};
extern Load w;
#endif // LOAD_H
