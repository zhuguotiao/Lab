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

private:
    Ui::MedicalRecordView *ui;
};

#endif // MEDICALRECORDVIEW_H
