#ifndef WELCOMEVIEW_H
#define WELCOMEVIEW_H

#include <QWidget>

namespace Ui {
class WelcomeView;
}

class WelcomeView : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeView(QWidget *parent = nullptr);
    ~WelcomeView();

private slots:


    void on_btDoctor_clicked();

    void on_btPatient_clicked();

    void on_btDrug_clicked();

    void on_btMedicalRecord_clicked();

    void on_btReserve_clicked();

    void on_btDataAnalysis_clicked();

    void on_btSave_clicked();

    void on_btResume_clicked();

    void on_btDoctorReport_clicked();

signals:

    void goDoctorView();

    void goPatientView();

    void goDrugView();

    void goMedicalRecordView();

    void goReserveView();

    void goAnalysisView();

    void goDoctorReportView();

private:
    Ui::WelcomeView *ui;
};

#endif // WELCOMEVIEW_H
