#ifndef MEDICALRECORDEDITVIEW_H
#define MEDICALRECORDEDITVIEW_H

#include <QWidget>
#include <QDataWidgetMapper>

namespace Ui {
class MedicalRecordEditView;
}

class MedicalRecordEditView : public QWidget
{
    Q_OBJECT

public:
    explicit MedicalRecordEditView(QWidget *parent = nullptr,int index=0);
    ~MedicalRecordEditView();

signals:
    void goPreviousView();

private slots:
    void on_btCancel_clicked();

    void on_btSave_clicked();

private:
    Ui::MedicalRecordEditView *ui;
     QDataWidgetMapper *dataMapper;
};


#endif // MEDICALRECORDEDITVIEW_H
