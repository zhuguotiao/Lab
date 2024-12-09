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

private:
    Ui::DrugView *ui;
};

#endif // DRUGVIEW_H
