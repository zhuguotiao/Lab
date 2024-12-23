#include "reserveview.h"
#include "ui_reserveview.h"
#include "idatabase.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>

ReserveView::ReserveView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReserveView)
{
    ui->setupUi(this);


    //一些个性化的设置，对表格的
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);

    IDatabase &iDatabase=IDatabase::getInstance();

    if(iDatabase.initReserveModel()){
        ui->tableView->setModel(iDatabase.tabModel);
        ui->tableView->setSelectionModel(iDatabase.selection);
    }

    ui->totalAndCurrent->setText("第1页");

}

ReserveView::~ReserveView()
{
    delete ui;
}

void ReserveView::on_btSearch_clicked()
{
    QString baseFilter = QString("patient_name LIKE '%%1%'").arg(ui->textSearch->text()); // 基础过滤条件
       qDebug() << "Initial filter string:" << baseFilter;

       // 获取排序条件
       QString orderClause;
       QString selectedOrder = ui->orderCombo->currentText();
        qDebug() <<  selectedOrder;
       if (selectedOrder == "按预约时间升序") {
           orderClause = "ORDER BY date ASC";
       } else if (selectedOrder == "按预约时间降序") {
           orderClause = "ORDER BY date DESC";
       }

       // 拼接最终的过滤条件
       QString filter = baseFilter;
       if (!orderClause.isEmpty()) {
           filter += " " + orderClause;
       }

       // 打印完整的过滤条件
       qDebug() << "Final filter string:" << filter;

       // 调用数据库实例的搜索方法
       IDatabase::getInstance().search(filter);
       ui->totalAndCurrent->setText("第1页");
}


void ReserveView::on_btEdit_clicked()
{
    //获取当前行号
    QModelIndex curIndex=IDatabase::getInstance().selection->currentIndex();

    emit goReserveEditView(curIndex.row());
}


void ReserveView::on_btNext_clicked()
{
    IDatabase &iDatabase = IDatabase::getInstance();

    int maxPage = iDatabase.getMaxPage();  // 获取最大页数

    if (iDatabase.currentPage < maxPage - 1) {  // 判断是否还有下一页
        iDatabase.setCurrentPage(iDatabase.currentPage + 1);
        ui->totalAndCurrent->setText(QString("第 %1 页")
                                     .arg(iDatabase.currentPage + 1));
    }
}


void ReserveView::on_btPrev_clicked()
{
    IDatabase &iDatabase = IDatabase::getInstance();

    if (iDatabase.currentPage > 0) {
        iDatabase.setCurrentPage(iDatabase.currentPage - 1);
        ui->totalAndCurrent->setText(QString("第 %1 页")
                                     .arg(iDatabase.currentPage + 1));
    }
}

