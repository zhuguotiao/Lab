#include "drugview.h"
#include "ui_drugview.h"
#include "idatabase.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>


DrugView::DrugView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrugView)
{
    ui->setupUi(this);


    //一些个性化的设置，对表格的
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);

    IDatabase &iDatabase=IDatabase::getInstance();

    if(iDatabase.initDrugModel()){
        ui->tableView->setModel(iDatabase.tabModel);
        ui->tableView->setSelectionModel(iDatabase.selection);
    }

    ui->totalAndCurrent->setText("第1页");

}

DrugView::~DrugView()
{
    delete ui;
}



void DrugView::on_btPrev_clicked()
{
    IDatabase &iDatabase = IDatabase::getInstance();

    if (iDatabase.currentPage > 0) {
        iDatabase.setCurrentPage(iDatabase.currentPage - 1);
        ui->totalAndCurrent->setText(QString("第 %1 页")
                                     .arg(iDatabase.currentPage + 1));
    }
}


void DrugView::on_btNext_clicked()
{
    IDatabase &iDatabase = IDatabase::getInstance();

    int maxPage = iDatabase.getMaxPage();  // 获取最大页数

    if (iDatabase.currentPage < maxPage - 1) {  // 判断是否还有下一页
        iDatabase.setCurrentPage(iDatabase.currentPage + 1);
        ui->totalAndCurrent->setText(QString("第 %1 页")
                                     .arg(iDatabase.currentPage + 1));
    }
}


void DrugView::on_btSearch_clicked()
{
    QString baseFilter = QString("name LIKE '%%1%'").arg(ui->textSearch->text()); // 基础过滤条件
       qDebug() << "Initial filter string:" << baseFilter;

       // 获取排序条件
       QString orderClause;
       QString selectedOrder = ui->orderCombo->currentText();
        qDebug() <<  selectedOrder;
       if (selectedOrder == "按库存升序") {
           orderClause = "ORDER BY inventory ASC";
       } else if (selectedOrder == "按库存降序") {
           orderClause = "ORDER BY inventory DESC";
       }else if (selectedOrder == "按名称降序") {
           orderClause = "ORDER BY name DESC";
       }else if (selectedOrder == "按名称升序") {
           orderClause = "ORDER BY name ASC";
       } else {
           orderClause = ""; // 默认不排序
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


void DrugView::on_btAdd_clicked()
{
    int curIndex=IDatabase::getInstance().addNewDrug();

    qDebug()<<curIndex;

    emit goDrugEditView(curIndex);
}


void DrugView::on_btDelete_clicked()
{
    IDatabase::getInstance().deleteCurrent();
}


void DrugView::on_btEdit_clicked()
{
    //获取当前行号
    QModelIndex curIndex=IDatabase::getInstance().selection->currentIndex();

    emit goDrugEditView(curIndex.row());
}


void DrugView::on_btImport_clicked()
{
    IDatabase::getInstance().importData();
}


void DrugView::on_btExport_clicked()
{
    IDatabase::getInstance().exportData();
}


void DrugView::on_btWarning_clicked()
{
    // 拼接最终的过滤条件
    QString filter = "inventory < 10";


    // 打印完整的过滤条件
    qDebug() << "Final filter string:" << filter;

    // 调用数据库实例的搜索方法
    IDatabase::getInstance().search(filter);
}

