#ifndef DRUGEDITVIEW_H
#define DRUGEDITVIEW_H

#include <QWidget>
#include <QDataWidgetMapper>

namespace Ui {
class DrugEditView;
}

class DrugEditView : public QWidget
{
    Q_OBJECT

public:
    explicit DrugEditView(QWidget *parent = nullptr,int index=0);
    ~DrugEditView();

signals:
    void goPreviousView();

private slots:
    void on_btSave_clicked();

    void on_btCancel_clicked();

private:
    Ui::DrugEditView *ui;
    QDataWidgetMapper *dataMapper;
};

#endif // DRUGEDITVIEW_H
