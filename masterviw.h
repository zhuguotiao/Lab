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

QT_BEGIN_NAMESPACE
namespace Ui { class MasterViw; }
QT_END_NAMESPACE

class MasterViw : public QWidget
{
    Q_OBJECT

public:
    MasterViw(QWidget *parent = nullptr);
    ~MasterViw();

public:
    void goLoginView();
    void goWelcomeView(const QString &type);

    void goDoctorView();
    void goDepartmentView();
    void goPatientEditView(int rowNo);
    void goPatientView();
    void goMedicalRecordView();
    void goDrugView();

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
    PatientEditView *patientEditView;
    PatientView *patientView;
    WelcomeView *welcomeView;
    MedicalRecordView *medicalRecordView;
    DrugView *drugView;
    QString type;

};
#endif // MASTERVIW_H
