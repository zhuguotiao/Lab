#include "medicalrecordview.h"
#include "ui_medicalrecordview.h"
#include "idatabase.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>

MedicalRecordView::MedicalRecordView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MedicalRecordView)
{
    ui->setupUi(this);

    //一些个性化的设置，对表格的
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);

    IDatabase &iDatabase=IDatabase::getInstance();

    if(iDatabase.initMedicalRecordModel()){
        ui->tableView->setModel(iDatabase.tabModel);
        ui->tableView->setSelectionModel(iDatabase.selection);
    }

    ui->totalAndCurrent->setText("第1页");

}

MedicalRecordView::~MedicalRecordView()
{
    delete ui;
}

void MedicalRecordView::on_btPrev_clicked()
{
    IDatabase &iDatabase = IDatabase::getInstance();

    if (iDatabase.currentPage > 0) {
        iDatabase.setCurrentPage(iDatabase.currentPage - 1);
        ui->totalAndCurrent->setText(QString("第 %1 页")
                                     .arg(iDatabase.currentPage + 1));
    }
}


void MedicalRecordView::on_btNext_clicked()
{
    IDatabase &iDatabase = IDatabase::getInstance();

    int maxPage = iDatabase.getMaxPage();  // 获取最大页数

    if (iDatabase.currentPage < maxPage - 1) {  // 判断是否还有下一页
        iDatabase.setCurrentPage(iDatabase.currentPage + 1);
        ui->totalAndCurrent->setText(QString("第 %1 页")
                                     .arg(iDatabase.currentPage + 1));
    }
}


void MedicalRecordView::on_btSearch_clicked()
{
    QString filter = QString("patientname LIKE '%%1%'").arg(ui->textSearch->text()); // 基础过滤条件

    qDebug() << "Initial filter string:" << filter;
    // 获取排序条件
    QString orderClause;
    QString selectedOrder = ui->orderCombo->currentText();
     qDebug() <<  selectedOrder;
    if (selectedOrder == "按日期升序") {
        orderClause = "ORDER BY date ASC";
    } else if (selectedOrder == "按日期降序") {
        orderClause = "ORDER BY date DESC";
    }else {
        orderClause = ""; // 默认不排序
    }

    if (!orderClause.isEmpty()) {
        filter += " " + orderClause;
    }

    // 打印完整的过滤条件
    qDebug() << "Final filter string:" << filter;

    // 调用数据库实例的搜索方法
    IDatabase::getInstance().search(filter);
    ui->totalAndCurrent->setText("第1页");
}


void MedicalRecordView::on_btAdd_clicked()
{
    int curIndex=IDatabase::getInstance().addNewMedicalRecord();
    qDebug()<<curIndex;
    emit goMedicalRecordEditView(curIndex);
}


void MedicalRecordView::on_btDelete_clicked()
{
    IDatabase::getInstance().deleteCurrent();
}


void MedicalRecordView::on_btEdit_clicked()
{
    //获取当前行号
    QModelIndex curIndex=IDatabase::getInstance().selection->currentIndex();

    emit goMedicalRecordEditView(curIndex.row());
}


void MedicalRecordView::on_btExport_clicked()
{
    IDatabase::getInstance().exportData();

}

