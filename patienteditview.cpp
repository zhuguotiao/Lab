#include "patienteditview.h"
#include "ui_patienteditview.h"
#include "idatabase.h"
#include <QSqlTableModel>
#include <QDebug>

PatientEditView::PatientEditView(QWidget *parent, int index) :
    QWidget(parent),
    ui(new Ui::PatientEditView)
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
    dataMapper->addMapping(ui->dbEditIDCard, tabModel->fieldIndex("ID_CARD"));
    dataMapper->addMapping(ui->dbSpinHeigh, tabModel->fieldIndex("HEIGHT"));
    dataMapper->addMapping(ui->dbSpinWeigh, tabModel->fieldIndex("WEIGHT"));
    dataMapper->addMapping(ui->dbEditMobile, tabModel->fieldIndex("MOBILEPHONE"));
    dataMapper->addMapping(ui->dbDateEditDOB, tabModel->fieldIndex("DOB"));
    dataMapper->addMapping(ui->dbComboSex, tabModel->fieldIndex("SEX"));
    dataMapper->addMapping(ui->dbCreatedTimeStamp, tabModel->fieldIndex("CREATEDTIMESTAMP"));

    // 设置当前索引
    dataMapper->setCurrentIndex(index);
}

PatientEditView::~PatientEditView()
{
    delete ui;
}

void PatientEditView::on_btSave_clicked()
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

void PatientEditView::on_btCancel_clicked()
{
    // 撤销更改
    IDatabase::getInstance().tabModel->revertAll();

    emit goPreviousView();
}
