#ifndef PATIENTVIEW_H
#define PATIENTVIEW_H

#include <QWidget>


namespace Ui {
class PatientView;
}

class PatientView : public QWidget
{
    Q_OBJECT

public:
    explicit PatientView(QWidget *parent = nullptr);
    ~PatientView();

private slots:
    void on_btAdd_clicked();

    void on_btSearch_clicked();

    void on_btDelete_clicked();

    void on_btEdit_clicked();


    void on_btNext_clicked();


    void on_btPrev_clicked();

    void on_btimport_clicked();

    void on_btExport_clicked();

signals:
    void goPatientEditView(int index);

private:
    Ui::PatientView *ui;


};

#endif // PATIENTVIEW_H
