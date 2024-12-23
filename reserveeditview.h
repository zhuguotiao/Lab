#ifndef RESERVEEDITVIEW_H
#define RESERVEEDITVIEW_H

#include <QWidget>
#include <QDataWidgetMapper>

namespace Ui {
class ReserveEditView;
}

class ReserveEditView : public QWidget
{
    Q_OBJECT

public:
    explicit ReserveEditView(QWidget *parent = nullptr,int index=0);
    ~ReserveEditView();

private slots:
    void on_btCancel_clicked();

    void on_btSave_clicked();




signals:
    void goPreviousView();

private:
    Ui::ReserveEditView *ui;
    QDataWidgetMapper *dataMapper;

     void  sendEmailWithQQ(const QString &msg);
};

#endif // RESERVEEDITVIEW_H
