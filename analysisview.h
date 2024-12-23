#ifndef ANALYSISVIEW_H
#define ANALYSISVIEW_H

#include <QWidget>

namespace Ui {
class AnalysisView;
}

class AnalysisView : public QWidget
{
    Q_OBJECT

public:
    explicit AnalysisView(QWidget *parent = nullptr);
    ~AnalysisView();

private slots:
    void on_tabWidget_currentChanged(int index);

private:
    Ui::AnalysisView *ui;

    // 加载医生模块的数据
    void loadDoctorData();

    // 加载病人模块的数据
    void loadPatientData();

    // 加载药品模块的数据
    void loadDrugData();

    // 加载就诊模块的数据
    void loadMedicalRecordData();


};

#endif // ANALYSISVIEW_H
