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
    bool initPatientModel();
    //查找函数
    bool searchPatient(QString filter);
    //删除患者
    bool deleteCurrentPatient();
    bool submitPatientEdit();
    void revertPatientEdit();

    int addNewPatient();

    //数据模型
    QSqlTableModel * patientTabModel;
    //选择模型
    QItemSelectionModel *thePatientSelection;
};

#endif // IDATABASE_H
