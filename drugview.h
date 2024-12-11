#ifndef DRUGVIEW_H
#define DRUGVIEW_H

#include <QWidget>

namespace Ui {
class DrugView;
}

class DrugView : public QWidget
{
    Q_OBJECT

public:
    explicit DrugView(QWidget *parent = nullptr);
    ~DrugView();

private slots:


    void on_btPrev_clicked();

    void on_btNext_clicked();

    void on_btSearch_clicked();

    void on_btAdd_clicked();

    void on_btDelete_clicked();

    void on_btEdit_clicked();

signals:
    void goDrugEditView(int index);

private:
    Ui::DrugView *ui;
};

#endif // DRUGVIEW_H
