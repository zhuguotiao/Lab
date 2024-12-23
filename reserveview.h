#ifndef RESERVEVIEW_H
#define RESERVEVIEW_H

#include <QWidget>

namespace Ui {
class ReserveView;
}

class ReserveView : public QWidget
{
    Q_OBJECT

public:
    explicit ReserveView(QWidget *parent = nullptr);
    ~ReserveView();

signals:
    void goReserveEditView(int index);

private slots:
    void on_btSearch_clicked();

    void on_btEdit_clicked();

    void on_btNext_clicked();

    void on_btPrev_clicked();

private:
    Ui::ReserveView *ui;
};

#endif // RESERVEVIEW_H
