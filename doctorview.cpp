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
    QString filter = QString("name LIKE '%%1%'").arg(ui->textSearch->text()); // 基础过滤条件
    qDebug() << "Initial filter string:" << filter;

    // 打印完整的过滤条件
    qDebug() << "Final filter string:" << filter;

    // 调用数据库实例的搜索方法
    IDatabase::getInstance().search(filter);
    ui->totalAndCurrent->setText("第1页");
}


void DoctorView::on_btAdd_clicked()
{
    int curIndex=IDatabase::getInstance().addNewDoctor();

    qDebug()<<curIndex;

    emit goDoctorEditView(curIndex);
}


void DoctorView::on_btDelete_clicked()
{
    IDatabase::getInstance().deleteCurrent();
}


void DoctorView::on_btEdit_clicked()
{
    //获取当前行号
    QModelIndex curIndex=IDatabase::getInstance().selection->currentIndex();

    emit goDoctorEditView(curIndex.row());
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


void DoctorView::on_btImport_clicked()
{
    IDatabase::getInstance().importData();
}


void DoctorView::on_btExport_clicked()
{
    IDatabase::getInstance().exportData();
}

