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

signals:

    void goDoctorView();

    void goPatientView();

    void goDrugView();

    void goMedicalRecordView();

    void goReserveView();

private:
    Ui::WelcomeView *ui;
};

#endif // WELCOMEVIEW_H
