#ifndef MASTERVIW_H
#define MASTERVIW_H

#include <QWidget>
#include "loginview.h"
#include "doctorview.h"
#include "patienteditview.h"
#include "patientview.h"
#include "welcomeview.h"
#include "medicalrecordview.h"
#include "drugview.h"
#include "doctoreditview.h"
#include "drugeditview.h"
#include "medicalrecordeditview.h"
#include "patientreserveview.h"
#include "reserveview.h"
#include  "reserveeditview.h"
#include "analysisview.h"
#include "doctorreportview.h"
#include "doctorreporteditview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MasterViw; }
QT_END_NAMESPACE

class MasterViw : public QWidget
{
    Q_OBJECT

public:
    MasterViw(QWidget *parent = nullptr);
    ~MasterViw();
    static QString username;


public:
    //页面跳转操作
    void goLoginView();
    void goWelcomeView(const QString &type);

    void goDoctorView();
    void goDoctorEditView(int rowNo);


    void goPatientEditView(int rowNo);
    void goPatientView();

    void goMedicalRecordView();
    void goMedicalRecordEditView(int rowNo);

    void goDrugView();
    void goDrugEditView(int rowNo);


    void goPatientReserveView();
    void goReserveView();
    void goReserveEditView(int rowNo);

    void goAnalysisView();

    void goDoctorReportView();
    void goDoctorReportEditView(int rowNo);


    void goPreviousView();


private slots:
    void on_btBack_clicked();

    void on_stackedWidget_currentChanged(int arg1);

    void on_btLogout_clicked();

private:

    void pushWidgetToStackView(QWidget *widget);

    Ui::MasterViw *ui;

    LoginView *loginView;

    DoctorView *doctorView;
    DoctorEditView *doctorEditView;

    PatientEditView *patientEditView;
    PatientView *patientView;

    WelcomeView *welcomeView;

    MedicalRecordView *medicalRecordView;
    MedicalRecordEditView *medicalRecordEditView;

    DrugView *drugView;
    DrugEditView *drugEditView;

    PatientReserveView *patientReserveView;
    ReserveView *reserveView;
    ReserveEditView *reserveEditView;

    AnalysisView *analysisView;


    DoctorReportView *doctorReportView;
    DoctorReportEditView *doctorReportEditView;

    QString type;

};
#endif // MASTERVIW_H
