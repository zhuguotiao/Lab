#ifndef DOCTORVIEW_H
#define DOCTORVIEW_H

#include <QWidget>

namespace Ui {
class DoctorView;
}

class DoctorView : public QWidget
{
    Q_OBJECT

public:
    explicit DoctorView(QWidget *parent = nullptr);
    ~DoctorView();

private slots:
    void on_btSearch_clicked();

    void on_btAdd_clicked();

    void on_btDelete_clicked();

    void on_btEdit_clicked();

    void on_btPrev_clicked();

    void on_btNext_clicked();

    void on_btImport_clicked();

    void on_btExport_clicked();

signals:
    void goDoctorEditView(int index);

private:
    Ui::DoctorView *ui;
};

#endif // DOCTORVIEW_H
