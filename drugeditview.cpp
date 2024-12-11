#include "drugeditview.h"
#include "ui_drugeditview.h"
#include "idatabase.h"
#include <QSqlTableModel>
#include <QDebug>


DrugEditView::DrugEditView(QWidget *parent,int index) :
    QWidget(parent),
    ui(new Ui::DrugEditView)
{
    ui->setupUi(this);

    dataMapper = new QDataWidgetMapper(this);
    QSqlTableModel *tabModel = IDatabase::getInstance().tabModel;
    dataMapper->setModel(tabModel);

    // 设置提交策略为 ManualSubmit
    dataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    // 绑定控件到模型字段
    dataMapper->addMapping(ui->dbEditID, tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->dbEditName, tabModel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->dbEditInventory, tabModel->fieldIndex("INVENTORY"));
    dataMapper->addMapping(ui->dbComboType, tabModel->fieldIndex("TYPE"));
    dataMapper->addMapping(ui->dbEditDose, tabModel->fieldIndex("DOSE"));



    // 设置当前索引
    dataMapper->setCurrentIndex(index);

}

DrugEditView::~DrugEditView()
{
    delete ui;
}

void DrugEditView::on_btSave_clicked()
{
    // 提交数据到模型
    dataMapper->submit();

    // 提交模型数据到数据库
    if (!IDatabase::getInstance().tabModel->submitAll()) {
        qDebug() << "Failed to submit data:" << IDatabase::getInstance().tabModel->lastError().text();
    } else {
        qDebug() << "Data saved successfully!";
    }

    // 刷新数据
    IDatabase::getInstance().loadPageData();

    emit goPreviousView();
}


void DrugEditView::on_btCancel_clicked()
{
    // 撤销更改
    IDatabase::getInstance().tabModel->revertAll();

    emit goPreviousView();
}

