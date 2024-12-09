#include "medicalrecordview.h"
#include "ui_medicalrecordview.h"

MedicalRecordView::MedicalRecordView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MedicalRecordView)
{
    ui->setupUi(this);
}

MedicalRecordView::~MedicalRecordView()
{
    delete ui;
}
