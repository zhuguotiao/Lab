#ifndef DOCTORREPORTVIEW_H
#define DOCTORREPORTVIEW_H

#include <QWidget>

namespace Ui {
class DoctorReportView;
}

class DoctorReportView : public QWidget
{
    Q_OBJECT

public:
    explicit DoctorReportView(QWidget *parent = nullptr);
    ~DoctorReportView();

private slots:
    void on_btSearch_clicked();

    void on_btAdd_clicked();

    void on_btDelete_clicked();

    void on_btEdit_clicked();

    void on_btimport_clicked();

    void on_btPrev_clicked();

    void on_btNext_clicked();


signals:
    void goDoctorReportEditView(int index);

private:
    Ui::DoctorReportView *ui;
};


#endif // DOCTORREPORTVIEW_H
