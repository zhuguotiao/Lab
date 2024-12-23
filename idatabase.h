#ifndef IDATABASE_H
#define IDATABASE_H

#include <QObject>
#include<QtSql>
#include <QSqlDatabase>
#include <QDataWidgetMapper>


class IDatabase : public QObject
{
    Q_OBJECT
public:

    static IDatabase &getInstance()
    {
        static IDatabase instance;
        return instance;
    }


    QString userLogin(QString username,QString password);



private:
    explicit IDatabase(QObject *parent = nullptr);

    IDatabase(IDatabase const &) = delete;


    void operator=(IDatabase const &) =delete;

    QSqlDatabase database;

    void initDatabase();






signals:

public:
    QString tableName;//表格名字
    //分页相关记录
    int pageSize;  // 每页数据量
    int currentPage;  // 当前页码
    int totalRecords;
    QString filter;//查询条件
    void setPageSize(int size);
    void setCurrentPage(int page);
    bool loadPageData();


    int getMaxPage() const;// 计算最大页数

    //导入和导出功能实现
    bool exportData();
    bool importData();

    //通用操作
    //查找函数
    bool search(QString filter);
    //删除患者
    bool deleteCurrent();
    bool submitEdit();
    void revertEdit();


    //1.患者管理相关
    bool initPatientModel();

    int addNewPatient();

    //数据模型
    QSqlTableModel * tabModel;
    //选择模型
    QItemSelectionModel *selection;

    //2.医生管理相关
    bool initDocotorModel();
    int addNewDoctor();



    //3.药品管理相关
    bool initDrugModel();
    int addNewDrug();

    //2.就诊记录管理相关
    bool initMedicalRecordModel();
    int addNewMedicalRecord();

    //预约相关
    bool insertReservation(const QString &doctor, const QDate &date, const QTime &time, const QString &patientName, const QString &patientEmail);

    bool initReserveModel();


};

#endif // IDATABASE_H
