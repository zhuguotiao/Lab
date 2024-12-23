#include "doctoreditview.h"
#include "ui_doctoreditview.h"
#include "idatabase.h"
#include <QSqlTableModel>
#include <QDebug>

DoctorEditView::DoctorEditView(QWidget *parent, int index) :
    QWidget(parent),
    ui(new Ui::DoctorEditView)
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
    dataMapper->addMapping(ui->dbEditEmail, tabModel->fieldIndex("EMAIL"));
    dataMapper->addMapping(ui->dbSpinAge, tabModel->fieldIndex("AGE"));
    dataMapper->addMapping(ui->dbComboSex, tabModel->fieldIndex("SEX"));
    dataMapper->addMapping(ui->dbComboxPosition, tabModel->fieldIndex("POSITION"));
    dataMapper->addMapping(ui->dbEditPracticingCertificate, tabModel->fieldIndex("PRACTICINGCERTIFICATE"));


    // 设置当前索引
    dataMapper->setCurrentIndex(index);

}

DoctorEditView::~DoctorEditView()
{
    delete ui;
}

void DoctorEditView::on_btSave_clicked()
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


void DoctorEditView::on_btCancel_clicked()
{
    // 撤销更改
    IDatabase::getInstance().tabModel->revertAll();

    emit goPreviousView();
}

