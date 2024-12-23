#include "analysisview.h"
#include "ui_analysisview.h"
#include <QDebug>
#include "idatabase.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QBarSeries>
#include <QBarSet>
#include <QPieSeries>
#include <QPieSlice>

AnalysisView::AnalysisView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnalysisView)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    loadDoctorData();  // 初始化时加载医生数据
}

AnalysisView::~AnalysisView()
{
    delete ui;
}

void AnalysisView::on_tabWidget_currentChanged(int index)
{
    switch (index) {
        case 0:
            // 医生模块，加载相关图表或数据
            loadDoctorData();
            break;
        case 1:
            // 病人模块，加载相关图表或数据
            loadPatientData();
            break;
        case 2:
            // 药品模块，加载相关图表或数据
            loadDrugData();
            break;
        case 3:
            // 就诊模块，加载相关图表或数据
            loadMedicalRecordData();
            break;
        default:
            // 其他标签页
            break;
    }
}

// 加载医生模块的数据
void AnalysisView::loadDoctorData()
{
    qDebug() << "加载医生数据";

    // 获取医生数据
    IDatabase &db = IDatabase::getInstance();
    db.initDocotorModel();  // 初始化医生数据模型
    db.pageSize = 10000;
    db.loadPageData();
    QSqlTableModel *doctorModel = db.tabModel;  // 获取医生数据表模型

    // 创建一个QPieSeries用于存储医生的职位信息
    QPieSeries *pieSeries = new QPieSeries();

    int juniorCount = 0, intermediateCount = 0, seniorCount = 0;

    // 统计医生职位信息
    for (int i = 0; i < doctorModel->rowCount(); ++i) {
        QString position = doctorModel->record(i).value("POSITION").toString();
        if (position == "初级") {
            juniorCount++;
        } else if (position == "中级") {
            intermediateCount++;
        } else if (position == "高级") {
            seniorCount++;
        }
    }

    // 将统计的数据添加到饼图中
    pieSeries->append("初级", juniorCount);
    pieSeries->append("中级", intermediateCount);
    pieSeries->append("高级", seniorCount);

    // 创建一个QChart并设置其标题
    QChart *chart = new QChart();
    chart->addSeries(pieSeries);
    chart->setTitle("医生职位分布");

    // 设置饼图的样式
    pieSeries->setLabelsVisible(true);  // 显示标签

    // 设置标签的位置
    for (QPieSlice *slice : pieSeries->slices()) {
        slice->setLabelPosition(QPieSlice::LabelOutside);  // 标签显示在外部
    }

    // 创建一个QChartView并将其设置到UI界面上
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->doctorChart->setChart(chart);  // 将QChart设置到现有的QChartView
}




// 加载病人模块的数据
void AnalysisView::loadPatientData()
{
    qDebug() << "加载病人数据";

    // 获取病人数据
    IDatabase &db = IDatabase::getInstance();
    db.initPatientModel();  // 初始化病人数据模型
    QSqlTableModel *patientModel = db.tabModel;  // 获取病人数据表模型
    db.pageSize=10000;
    db.loadPageData();

    // 创建一个QBarSet用于存储病人的性别信息
    QBarSet *patientSet = new QBarSet("病人性别");
    QBarSeries *barSeries = new QBarSeries();

    int maleCount = 0, femaleCount = 0;
    qDebug()<<"病人人数"<<patientModel->rowCount();
    for (int i = 0; i < patientModel->rowCount(); ++i) {
        QString gender = patientModel->record(i).value("SEX").toString();
        qDebug()<<"病人性别"<<gender;

        if (gender == "男") {
            maleCount++;
        } else {
            femaleCount++;
        }
    }

    *patientSet << maleCount << femaleCount;

    // 将QBarSet加入到QBarSeries
    barSeries->append(patientSet);

    // 创建一个QChart并设置其标题
    QChart *chart = new QChart();
    chart->addSeries(barSeries);
    chart->setTitle("病人性别分布");

    // 设置X轴和Y轴
    chart->createDefaultAxes();

    // 获取Y轴并设置为整数显示
    QValueAxis *yAxis = new QValueAxis();
    yAxis->setTickCount(6); // 设置Y轴的刻度数量
    yAxis->setMinorTickCount(0);  // 设置不显示次级刻度
    yAxis->setLabelFormat("%d");  // 设置标签格式为整数
    chart->setAxisY(yAxis, barSeries);

    // 直接将QChart设置到QChartView中
    ui->patientChart->setChart(chart);  // 直接设置QChart，不需要QChartView
}

// 加载药品模块的数据
void AnalysisView::loadDrugData()
{
    qDebug() << "加载药品数据";
    // 获取药品数据
    IDatabase &db = IDatabase::getInstance();
    db.initDrugModel();  // 初始化药品数据模型
    QSqlTableModel *drugModel = db.tabModel;  // 获取药品数据表模型
    db.pageSize = 10000;
    db.loadPageData();

    // 创建一个QBarSet用于存储药品类型信息
    QBarSet *drugSet = new QBarSet("药品类型");
    QBarSeries *barSeries = new QBarSeries();

    int prescriptionCount = 0, overCounterCount = 0;
    for (int i = 0; i < drugModel->rowCount(); ++i) {
        QString type = drugModel->record(i).value("TYPE").toString();
        if (type == "处方") {
            prescriptionCount++;
        } else if (type == "非处方") {
            overCounterCount++;
        }
    }

    *drugSet << prescriptionCount << overCounterCount;

    // 将QBarSet加入到QBarSeries
    barSeries->append(drugSet);

    // 创建一个QChart并设置其标题
    QChart *chart = new QChart();
    chart->addSeries(barSeries);
    chart->setTitle("药品类型分布");

    // 设置X轴和Y轴
    chart->createDefaultAxes();

    // 获取Y轴并设置为整数显示
    QValueAxis *yAxis = new QValueAxis();
    yAxis->setTickCount(6); // 设置Y轴的刻度数量
    yAxis->setMinorTickCount(0);  // 设置不显示次级刻度
    yAxis->setLabelFormat("%d");  // 设置标签格式为整数
    chart->setAxisY(yAxis, barSeries);

    // 直接将QChart设置到QChartView中
    ui->drugChart->setChart(chart);  // 直接设置QChart，不需要QChartView
}


// 加载就诊模块的数据
void AnalysisView::loadMedicalRecordData()
{
    qDebug() << "加载就诊数据";

    // 获取就诊数据
    IDatabase &db = IDatabase::getInstance();
    db.initMedicalRecordModel();  // 初始化就诊数据模型
    QSqlTableModel *medicalRecordModel = db.tabModel;  // 获取就诊数据表模型
    db.pageSize = 10000;
    db.loadPageData();

    // 用一个QMap来存储日期和对应的就诊次数
    QMap<QDate, int> dateVisitCount;

    // 遍历数据，统计每个日期的就诊次数
    for (int i = 0; i < medicalRecordModel->rowCount(); ++i) {
        QString dateString = medicalRecordModel->record(i).value("DATE").toString();
        QDate date = QDate::fromString(dateString, "yyyy-MM-dd");  // 假设日期格式是 "yyyy-MM-dd"

        // 增加日期的就诊次数
        if (date.isValid()) {
            dateVisitCount[date]++;
        }
    }

    // 创建一个QLineSeries用于存储就诊次数的时间变化图
    QLineSeries *lineSeries = new QLineSeries();

    // 将日期按顺序插入到QLineSeries中
    QList<QDate> sortedDates = dateVisitCount.keys();  // 获取所有日期并排序
    std::sort(sortedDates.begin(), sortedDates.end());

    for (const QDate &date : sortedDates) {
        int visitCount = dateVisitCount[date];
        lineSeries->append(date.toJulianDay(), visitCount);  // 将日期转换为Julian Day作为X轴
    }

    // 创建一个QChart并设置其标题
    QChart *chart = new QChart();
    chart->addSeries(lineSeries);
    chart->setTitle("就诊次数随时间变化");

    // 设置X轴和Y轴
    chart->createDefaultAxes();

    // 设置X轴为QDateTimeAxis，以便显示日期
    QDateTimeAxis *axisX = new QDateTimeAxis();
    axisX->setFormat("yyyy-MM-dd");  // 设置日期格式为"年-月-日"
    axisX->setTitleText("日期");
    chart->setAxisX(axisX, lineSeries);  // 设置X轴

    // 直接将QChart设置到QChartView中
    ui->medicalRecordChart->setChart(chart);  // 直接设置QChart，不需要QChartView
}



