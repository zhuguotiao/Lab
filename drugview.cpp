#include "drugview.h"
#include "ui_drugview.h"

DrugView::DrugView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrugView)
{
    ui->setupUi(this);
}

DrugView::~DrugView()
{
    delete ui;
}
