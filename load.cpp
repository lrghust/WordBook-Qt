#include "load.h"
#include "ui_load.h"
#include "WordBook.h"


Load::Load(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Load)
{
    ui->setupUi(this);
    //ui->bakpath->setPlaceholderText("不输入则为默认路径");
    L.elem=NULL;
    Ls.elem=NULL;
    H.elem=NULL;
}

Load::~Load()
{
    delete ui;
}

void Load::on_ok_clicked()
{
    if(ui->path->text().isEmpty()){
        QMessageBox::information(this,"Error","输入路径为空！");
    }
    else{
        path=ui->path->text();
        QByteArray path_=path.toLatin1();
        char *path_s=path_.data();
        if(init(path_s)){
            ui->count->setText(QString::number(L.length+1));
            ct2+=ct1;
            ui->ct1->setText(QString::number(ct1));
            ui->ct2->setText(QString::number(ct2));
            ui->ct3->setText(QString::number(ct3));
            flag_path=1;
        }
        else{
            QMessageBox::information(this,"Error","读取文件初始化失败！");
        }
    }
}

void Load::on_search_clicked()
{
    ui->pl1->clear();
    ui->pl2->clear();
    ui->pl3->clear();
    if(ui->word->text().isEmpty()){
        QMessageBox::information(this,"Error","输入单词为空！");
    }
    else if(flag_path==0){
        QMessageBox::information(this,"Error","请先录入或恢复数据！");
    }
    else{
        word=ui->word->text();
        QByteArray word_=word.toLatin1();
        char *word_s=word_.data();
        clock_t start=clock();
        int w1=searchUnsortedSqList(L,word_s);
        if(w1==-1){
            QMessageBox::information(this,"Error","未检索到所查单词！");
            return;
        }
        clock_t end=clock();
        t1=(double)(end-start)/CLOCKS_PER_SEC*1000.0;

        start=clock();
        int w2=searchSortedSqList(Ls,word_s);
        end=clock();
        t2=(double)(end-start)/CLOCKS_PER_SEC*1000.0;

        start=clock();
        HashElemType *w3=searchHash(H,word_s);
        end=clock();
        t3=(double)(end-start)/CLOCKS_PER_SEC*1000.0;
        //耗时输出
        ui->t1->setText(QString::number(t1));
        ui->t2->setText(QString::number(t2));
        ui->t3->setText(QString::number(t3));
        //出现次数输出
        c1=L.elem[w1-1].count;
        c2=Ls.elem[w2-1].count;
        c3=w3->count;
        ui->c1->setText(QString::number(c1));
        ui->c2->setText(QString::number(c2));
        ui->c3->setText(QString::number(c3));
        //页码-行数栏输出
        WordInfo *p1=L.elem[w1-1].info.next;
        while(p1){
            QString pl="Page:"+QString::number(p1->pages)+"    Line:"+QString::number(p1->lines);
            ui->pl1->append(pl);
            p1=p1->next;
        }
        QString pl1="Page:"+QString::number(L.elem[w1-1].info.pages)+"    Line:"+QString::number(L.elem[w1-1].info.lines);
        ui->pl1->append(pl1);

        WordInfo *p2=Ls.elem[w2-1].info.next;
        while(p2){
            QString pl="Page:"+QString::number(p2->pages)+"    Line:"+QString::number(p2->lines);
            ui->pl2->append(pl);
            p2=p2->next;
        }
        QString pl2="Page:"+QString::number(Ls.elem[w2-1].info.pages)+"    Line:"+QString::number(Ls.elem[w2-1].info.lines);
        ui->pl2->append(pl2);

        WordInfo *p3=w3->info.next;
        while(p3){
            QString pl="Page:"+QString::number(p3->pages)+"    Line:"+QString::number(p3->lines);
            ui->pl3->append(pl);
            p3=p3->next;
        }
        QString pl3="Page:"+QString::number(w3->info.pages)+"    Line:"+QString::number(w3->info.lines);
        ui->pl3->append(pl3);
    }
}



void Load::on_pushButton_clicked()
{
    path=QFileDialog::getOpenFileName(this,tr("File Path"),"/");
    ui->path->setText(path);
}

void Load::on_pushButton_2_clicked()
{
    bakpath=QFileDialog::getOpenFileName(this,tr("File Path"),"/");
    ui->bakpath->setText(bakpath);
}

void Load::on_pushButton_3_clicked()
{
    if(ui->bakpath->text().isEmpty())
        QMessageBox::information(this,"Error","输入路径为空！");
    else{
        bakpath=ui->bakpath->text();
        char *path_=bakpath.toLatin1().data();
        if(!loadData(path_)){
            QMessageBox::information(this,"Error","数据恢复失败！");
        }
        else{
            ui->count->setText(QString::number(L.length+1));
            ui->ct1->setText(QString::number(ct1));
            ui->ct2->setText(QString::number(ct2));
            ui->ct3->setText(QString::number(ct3));
            flag_path=1;
        }
    }
}

void Load::on_pushButton_4_clicked()
{
    savepath=QFileDialog::getExistingDirectory(this,tr("File Path"),"/");
    if(!savepath.isEmpty())
        savepath=savepath+"/save.dat";
    ui->savepath->setText(savepath);
}

void Load::on_save_clicked()
{
    if(ui->savepath->text().isEmpty())
        QMessageBox::information(this,"Error","输入路径为空！");
    else{
        savepath=ui->savepath->text();
        char *path=savepath.toLatin1().data();
        if(!saveData(path)){
            QMessageBox::information(this,"Error","数据保存失败！");
        }
        else{
            QMessageBox::information(this,"Error","数据保存成功！");
        }
    }
}

void Load::on_unsort_toggled(bool checked)
{
    if(checked)
        flag_traverse=1;
}

void Load::on_sort_toggled(bool checked)
{
    if(checked)
        flag_traverse=2;
}

void Load::on_hash_toggled(bool checked)
{
    if(checked)
        flag_traverse=3;
}

void Load::on_traverse_clicked()
{
    ui->print->clear();
    if(flag_path==0){
        QMessageBox::information(this,"Error","请先录入或恢复数据！");
        return;
    }
    switch (flag_traverse) {
    case 0:
        QMessageBox::information(this,"Error","请选择一种数据结构！");
        break;
    case 1:
        traverse_text.clear();
        traverseSqList(L,visitSqList);
        ui->print->setText(traverse_text);
        break;
    case 2:
        traverse_text.clear();
        traverseSqList(Ls,visitSqList);
        ui->print->setText(traverse_text);
        break;
    case 3:
        traverse_text.clear();
        traverseHash(H,visitHash);
        ui->print->setText(traverse_text);
        break;
    default:
        break;
    }
}

