#include "load.h"
#include "ui_load.h"

Load::Load(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Load)
{
    ui->setupUi(this);
}

Load::~Load()
{
    delete ui;
}
