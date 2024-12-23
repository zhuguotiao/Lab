#include "doctorreporteditview.h"
#include "ui_doctorreporteditview.h"
#include "idatabase.h"
#include <QSqlTableModel>
#include <QDebug>

DoctorReportEditView::DoctorReportEditView(QWidget *parent, int index) :
    QWidget(parent),
    ui(new Ui::DoctorReportEditView)
{
    ui->setupUi(this);

    populateDoctorsComboBox();

    dataMapper = new QDataWidgetMapper(this);
    QSqlTableModel *tabModel = IDatabase::getInstance().tabModel;
    dataMapper->setModel(tabModel);

    // 设置提交策略为 ManualSubmit
    dataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    // 绑定控件到模型字段
    dataMapper->addMapping(ui->dbEditID, tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->dbEditDoctorName, tabModel->fieldIndex("DOCTORNAME"));
    dataMapper->addMapping(ui->dbComboPatientName, tabModel->fieldIndex("PATIENTNAME"));

    dataMapper->addMapping(ui->dbEditcCreateTime, tabModel->fieldIndex("CREATETIME"));
    dataMapper->addMapping(ui->dbEditConsultation, tabModel->fieldIndex("CONSULTATION"));
    dataMapper->addMapping(ui->dbEditTreatmentEffect, tabModel->fieldIndex("TREATMENTEFFECT"));
    dataMapper->addMapping(ui->dbEditPatientFeedback, tabModel->fieldIndex("PATIENTFEEDBACK"));


    // 设置当前索引
    dataMapper->setCurrentIndex(index);
}

DoctorReportEditView::~DoctorReportEditView()
{
    delete ui;
}

void DoctorReportEditView::on_btCancel_clicked()
{
    // 撤销更改
    IDatabase::getInstance().tabModel->revertAll();

    emit goPreviousView();
}


void DoctorReportEditView::on_btSave_clicked()
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

void DoctorReportEditView::populateDoctorsComboBox()
{
    // 获取当前数据库连接
    QSqlDatabase db = QSqlDatabase::database();  // 默认使用已配置的数据库连接
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return;
    }

    // 创建查询对象
    QSqlQuery query(db);
    query.exec("SELECT name FROM patient");  // 假设医生表的名字是 doctor，字段名是 name

    // 将查询到的医生名字添加到下拉框
    while (query.next()) {
        QString patientName = query.value(0).toString();
        ui->dbComboPatientName->addItem(patientName);  // 将患者名称添加到下拉框
    }

}

