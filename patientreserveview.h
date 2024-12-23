#ifndef PATIENTRESERVEVIEW_H
#define PATIENTRESERVEVIEW_H

#include <QWidget>

namespace Ui {
class PatientReserveView;
}

class PatientReserveView : public QWidget
{
    Q_OBJECT

public:
    explicit PatientReserveView(QWidget *parent = nullptr);
    ~PatientReserveView();

private slots:
    void on_btReserve_clicked();

private:
    Ui::PatientReserveView *ui;
    void populateDoctorsComboBox();

    void sendEmailWithQQ();
};

#endif // PATIENTRESERVEVIEW_H
