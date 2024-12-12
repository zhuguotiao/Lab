#ifndef MEDICALRECORDVIEW_H
#define MEDICALRECORDVIEW_H

#include <QWidget>

namespace Ui {
class MedicalRecordView;
}

class MedicalRecordView : public QWidget
{
    Q_OBJECT

public:
    explicit MedicalRecordView(QWidget *parent = nullptr);
    ~MedicalRecordView();

private slots:


    void on_btPrev_clicked();

    void on_btNext_clicked();

    void on_btSearch_clicked();

    void on_btAdd_clicked();

    void on_btDelete_clicked();

    void on_btEdit_clicked();

    void on_btExport_clicked();

signals:
    void goMedicalRecordEditView(int index);

private:
    Ui::MedicalRecordView *ui;
};

#endif // MEDICALRECORDVIEW_H
