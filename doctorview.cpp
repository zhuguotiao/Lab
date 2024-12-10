#include "doctorview.h"
#include "ui_doctorview.h"
#include "idatabase.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>


DoctorView::DoctorView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoctorView)
{
    ui->setupUi(this);

    //一些个性化的设置，对表格的
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);

    IDatabase &iDatabase=IDatabase::getInstance();

    if(iDatabase.initDocotorModel()){
        ui->tableView->setModel(iDatabase.tabModel);
        ui->tableView->setSelectionModel(iDatabase.selection);
    }

    ui->totalAndCurrent->setText("第1页");
}

DoctorView::~DoctorView()
{
    delete ui;
}

void DoctorView::on_btSearch_clicked()
{

}


void DoctorView::on_btAdd_clicked()
{

}


void DoctorView::on_btDelete_clicked()
{
    IDatabase::getInstance().deleteCurrent();
}


void DoctorView::on_btEdit_clicked()
{
    //获取当前行号
    QModelIndex curIndex=IDatabase::getInstance().selection->currentIndex();

    // emit goPatientEditView(curIndex.row());
}


void DoctorView::on_btPrev_clicked()
{
    IDatabase &iDatabase = IDatabase::getInstance();

    if (iDatabase.currentPage > 0) {
        iDatabase.setCurrentPage(iDatabase.currentPage - 1);
        ui->totalAndCurrent->setText(QString("第 %1 页")
                                     .arg(iDatabase.currentPage + 1));
    }
}


void DoctorView::on_btNext_clicked()
{
    IDatabase &iDatabase = IDatabase::getInstance();

    int maxPage = iDatabase.getMaxPage();  // 获取最大页数

    if (iDatabase.currentPage < maxPage - 1) {  // 判断是否还有下一页
        iDatabase.setCurrentPage(iDatabase.currentPage + 1);
        ui->totalAndCurrent->setText(QString("第 %1 页")
                                     .arg(iDatabase.currentPage + 1));
    }
}

