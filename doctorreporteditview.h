#ifndef DOCTORREPORTEDITVIEW_H
#define DOCTORREPORTEDITVIEW_H

#include <QWidget>
#include <QDataWidgetMapper>

namespace Ui {
class DoctorReportEditView;
}

class DoctorReportEditView : public QWidget
{
    Q_OBJECT

public:
    explicit DoctorReportEditView(QWidget *parent = nullptr,int index=0);
    ~DoctorReportEditView();

signals:
    void goPreviousView();

private slots:
    void on_btCancel_clicked();

    void on_btSave_clicked();

private:
    Ui::DoctorReportEditView *ui;
    QDataWidgetMapper *dataMapper;
    void populateDoctorsComboBox();
};

#endif // DOCTORREPORTEDITVIEW_H
