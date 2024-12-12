#include "medicalrecordeditview.h"
#include "ui_medicalrecordeditview.h"
#include "idatabase.h"
#include <QSqlTableModel>
#include <QDebug>

MedicalRecordEditView::MedicalRecordEditView(QWidget *parent, int index) :
    QWidget(parent),
    ui(new Ui::MedicalRecordEditView)
{
    ui->setupUi(this);
    dataMapper = new QDataWidgetMapper(this);
    QSqlTableModel *tabModel = IDatabase::getInstance().tabModel;
    dataMapper->setModel(tabModel);

    // 设置提交策略为 ManualSubmit
    dataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    // 绑定控件到模型字段
    dataMapper->addMapping(ui->dbEditID, tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->dbEditDoctorName, tabModel->fieldIndex("DOCTORNAME"));
    dataMapper->addMapping(ui->dbEditPatientName, tabModel->fieldIndex("PATIENTNAME"));
    dataMapper->addMapping(ui->dbEditDate, tabModel->fieldIndex("DATE"));
    dataMapper->addMapping(ui->dbEditResult, tabModel->fieldIndex("Result"));
    dataMapper->addMapping(ui->dbEditDrug, tabModel->fieldIndex("DRUG"));

    // 设置当前索引
    dataMapper->setCurrentIndex(index);
}

MedicalRecordEditView::~MedicalRecordEditView()
{
    delete ui;
}

void MedicalRecordEditView::on_btCancel_clicked()
{
    // 撤销更改
    IDatabase::getInstance().tabModel->revertAll();

    emit goPreviousView();
}


void MedicalRecordEditView::on_btSave_clicked()
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

