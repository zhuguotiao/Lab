#ifndef PATIENTEDITVIEW_H
#define PATIENTEDITVIEW_H

#include <QWidget>
#include <QDataWidgetMapper>

namespace Ui {
class PatientEditView;
}

class PatientEditView : public QWidget
{
    Q_OBJECT

public:
    explicit PatientEditView(QWidget *parent = nullptr,int index=0);
    ~PatientEditView();

private slots:

    void on_btSave_clicked();

    void on_btCancel_clicked();

private:
    Ui::PatientEditView *ui;
    QDataWidgetMapper *dataMapper;

signals:
    void goPreviousView();

};

#endif // PATIENTEDITVIEW_H
