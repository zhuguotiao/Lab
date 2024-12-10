#include "patientview.h"
#include "ui_patientview.h"
#include "idatabase.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>

PatientView::PatientView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientView)
{
    ui->setupUi(this);

    //一些个性化的设置，对表格的
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);

    IDatabase &iDatabase=IDatabase::getInstance();

    if(iDatabase.initPatientModel()){
        ui->tableView->setModel(iDatabase.tabModel);
        ui->tableView->setSelectionModel(iDatabase.selection);
    }

    ui->totalAndCurrent->setText("第1页");



}

PatientView::~PatientView()
{
    delete ui;
}

void PatientView::on_btAdd_clicked()
{
    int curIndex=IDatabase::getInstance().addNewPatient();
    qDebug()<<curIndex;
    emit goPatientEditView(curIndex);
}


void PatientView::on_btSearch_clicked()
{
    QString filter = QString("name LIKE '%%1%'").arg(ui->textSearch->text()); // 基础过滤条件
    qDebug() << "Initial filter string:" << filter;

    // 获取 QGroupBox 中的所有 QRadioButton，并检查是否有被选中的按钮
    QList<QRadioButton*> radioButtons = ui->sexBox->findChildren<QRadioButton*>();
    for (QRadioButton* button : radioButtons) {
        if (button->isChecked() && button->text() != "不限") {
            // 将性别过滤条件添加到 filter 中
            filter += QString(" AND SEX = '%1'").arg(button->text());
            qDebug() << "Added gender filter:" << button->text();
        }
    }

    // 获取排序字段和顺序
    QString orderByField1, orderByField2;
    QString orderDirection1, orderDirection2;

    // 选择排序字段和顺序
    orderByField1 = "DOB";


    if (ui->ageBox->currentIndex() == 0) {
        orderDirection1 = "ASC"; // 正序
    } else {
        orderDirection1 = "DESC"; // 倒序
    }

    orderByField2 = "CREATEDTIMESTAMP";


    if (ui->createdTimeBox->currentIndex() == 0) {
        orderDirection2 = "ASC"; // 正序
    } else {
        orderDirection2 = "DESC"; // 倒序
    }

    // 构建 ORDER BY 子句
    QString orderByClause;
    if (!orderByField1.isEmpty()) {
        orderByClause += QString(" ORDER BY %1 %2").arg(orderByField1).arg(orderDirection1);
    }
    if (!orderByField2.isEmpty()) {
        if (!orderByClause.isEmpty()) {
            orderByClause += ", "; // 添加逗号分隔多个排序字段
        }
        orderByClause += QString("%1 %2").arg(orderByField2).arg(orderDirection2);
    }

    // 将排序条件添加到过滤条件中
    if (!orderByClause.isEmpty()) {
        filter += orderByClause;
        qDebug() << "Added order by condition:" << orderByClause;
    }

    // 打印完整的过滤条件
    qDebug() << "Final filter string:" << filter;

    // 调用数据库实例的搜索方法
    IDatabase::getInstance().search(filter);
    ui->totalAndCurrent->setText("第1页");

}


void PatientView::on_btDelete_clicked()
{
    IDatabase::getInstance().deleteCurrent();
}


void PatientView::on_btEdit_clicked()
{
    //获取当前行号
    QModelIndex curIndex=IDatabase::getInstance().selection->currentIndex();

    emit goPatientEditView(curIndex.row());
}

void PatientView::on_btNext_clicked() {
    IDatabase &iDatabase = IDatabase::getInstance();

    int maxPage = iDatabase.getMaxPage();  // 获取最大页数

    if (iDatabase.currentPage < maxPage - 1) {  // 判断是否还有下一页
        iDatabase.setCurrentPage(iDatabase.currentPage + 1);
        ui->totalAndCurrent->setText(QString("第 %1 页")
                                     .arg(iDatabase.currentPage + 1));
    }
}

void PatientView::on_btPrev_clicked() {
    IDatabase &iDatabase = IDatabase::getInstance();

    if (iDatabase.currentPage > 0) {
        iDatabase.setCurrentPage(iDatabase.currentPage - 1);
        ui->totalAndCurrent->setText(QString("第 %1 页")
                                     .arg(iDatabase.currentPage + 1));
    }
}

void PatientView::on_btExport_clicked()
{
    IDatabase::getInstance().exportData();
}

void PatientView::on_btimport_clicked()
{
    IDatabase::getInstance().importData();
}
