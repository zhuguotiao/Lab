#include "idatabase.h"
#include <QUuid>
#include <QFile>
#include <QTextStream>
#include <QSqlRecord>
#include <QFileDialog>
#include <QSqlQuery>
#include <QDebug>
#include "masterviw.h"

void IDatabase::initDatabase()
{
    //加载数据库驱动
    database=QSqlDatabase::addDatabase("QSQLITE");
    QString aFile="‪../../../../../../Lab4a.db";
    database.setDatabaseName(aFile);

    if(!database.open()){
        qDebug()<<"failed to open database";
     }else{
        qDebug()<<"open database successfully";
    }
}

bool IDatabase::initPatientModel()
{
    initDatabase();
    filter="";
    tabModel=new QSqlTableModel(this,database);
    tabModel->setTable("patient");
    //设置数据保存方式，按行还是按列
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //设置排序方式
    tabModel->setSort(tabModel->fieldIndex("name"),Qt::AscendingOrder);
    if(!(tabModel->select()))
        return false;

    tableName="patient";
    // 设置列标题（中文）
    tabModel->setHeaderData(tabModel->fieldIndex("ID"), Qt::Horizontal, "编号");
    tabModel->setHeaderData(tabModel->fieldIndex("NAME"), Qt::Horizontal, "姓名");
    tabModel->setHeaderData(tabModel->fieldIndex("HEIGHT"), Qt::Horizontal, "身高");
    tabModel->setHeaderData(tabModel->fieldIndex("WEIGHT"), Qt::Horizontal, "体重");
    tabModel->setHeaderData(tabModel->fieldIndex("DOB"), Qt::Horizontal, "出生日期");
    tabModel->setHeaderData(tabModel->fieldIndex("ID_CARD"), Qt::Horizontal, "身份证");

    tabModel->setHeaderData(tabModel->fieldIndex("SEX"), Qt::Horizontal, "性别");
    tabModel->setHeaderData(tabModel->fieldIndex("MOBILEPHONE"), Qt::Horizontal, "电话");
    tabModel->setHeaderData(tabModel->fieldIndex("CREATEDTIMESTAMP"), Qt::Horizontal, "创建时间");

    qDebug()<<tabModel;

    selection=new QItemSelectionModel(tabModel);

    pageSize = 5; // 设置每页数据量
    currentPage = 0; // 初始页码为0

    return loadPageData();
}


bool IDatabase::initDocotorModel()
{
    initDatabase();

    filter="";
    tabModel=new QSqlTableModel(this,database);
    tabModel->setTable("doctor");
    //设置数据保存方式，按行还是按列
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //设置排序方式
    tabModel->setSort(tabModel->fieldIndex("name"),Qt::AscendingOrder);
    if(!(tabModel->select()))
        return false;

    tableName="doctor";
    // 设置列标题（中文）
    tabModel->setHeaderData(tabModel->fieldIndex("ID"), Qt::Horizontal, "编号");
    tabModel->setHeaderData(tabModel->fieldIndex("NAME"), Qt::Horizontal, "姓名");
    tabModel->setHeaderData(tabModel->fieldIndex("AGE"), Qt::Horizontal, "年龄");
    tabModel->setHeaderData(tabModel->fieldIndex("ID_CARD"), Qt::Horizontal, "身份证");

    tabModel->setHeaderData(tabModel->fieldIndex("SEX"), Qt::Horizontal, "性别");
    tabModel->setHeaderData(tabModel->fieldIndex("EMAIL"), Qt::Horizontal, "邮箱");
    tabModel->setHeaderData(tabModel->fieldIndex("PRACTICINGCERTIFICATE"), Qt::Horizontal, "执业证书");
    tabModel->setHeaderData(tabModel->fieldIndex("POSITION"), Qt::Horizontal, "职称");


    qDebug()<<tabModel;

    selection=new QItemSelectionModel(tabModel);

    pageSize = 5; // 设置每页数据量
    currentPage = 0; // 初始页码为0

    return loadPageData();
}

int IDatabase::addNewDoctor()
{
    //在末尾添加一个记录
    tabModel->insertRow(tabModel->rowCount(),QModelIndex());
    //创建最后一行的MOdelIndex
    QModelIndex curIndex=tabModel->index(tabModel->rowCount()-1,1);

    int curRecNo=curIndex.row();
    QSqlRecord curRec=tabModel->record(curRecNo);

    curRec.setValue("POSITION","初级");

    curRec.setValue("SEX","男");
    curRec.setValue("ID",QUuid::createUuid().toString(QUuid::WithBraces));

    tabModel->setRecord(curRecNo,curRec);

    return curIndex.row();
}

bool IDatabase::initDrugModel()
{
    initDatabase();
    filter="";
    tabModel=new QSqlTableModel(this,database);
    tabModel->setTable("drug");
    //设置数据保存方式，按行还是按列
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //设置排序方式
    tabModel->setSort(tabModel->fieldIndex("name"),Qt::AscendingOrder);
    if(!(tabModel->select()))
        return false;

    tableName="drug";
    // 设置列标题（中文）
    tabModel->setHeaderData(tabModel->fieldIndex("ID"), Qt::Horizontal, "编号");
    tabModel->setHeaderData(tabModel->fieldIndex("NAME"), Qt::Horizontal, "名称");
    tabModel->setHeaderData(tabModel->fieldIndex("DOSE"), Qt::Horizontal, "剂量");
    tabModel->setHeaderData(tabModel->fieldIndex("INVENTORY"), Qt::Horizontal, "库存");
    tabModel->setHeaderData(tabModel->fieldIndex("TYPE"), Qt::Horizontal, "类型");


    qDebug()<<tabModel;

    selection=new QItemSelectionModel(tabModel);

    pageSize = 5; // 设置每页数据量
    currentPage = 0; // 初始页码为0

    return loadPageData();
}

int IDatabase::addNewDrug()
{
    //在末尾添加一个记录
    tabModel->insertRow(tabModel->rowCount(),QModelIndex());
    //创建最后一行的MOdelIndex
    QModelIndex curIndex=tabModel->index(tabModel->rowCount()-1,1);

    int curRecNo=curIndex.row();
    QSqlRecord curRec=tabModel->record(curRecNo);

    curRec.setValue("ID",QUuid::createUuid().toString(QUuid::WithBraces));
    curRec.setValue("TYPE","处方");


    tabModel->setRecord(curRecNo,curRec);

    return curIndex.row();
}

bool IDatabase::initMedicalRecordModel()
{
    initDatabase();
    filter="";
    tabModel=new QSqlTableModel(this,database);
    tabModel->setTable("medicalrecord");
    //设置数据保存方式，按行还是按列
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //设置排序方式
    tabModel->setSort(tabModel->fieldIndex("name"),Qt::AscendingOrder);
    if(!(tabModel->select()))
        return false;

    tableName="medicalrecord";
    // 设置列标题（中文）
    tabModel->setHeaderData(tabModel->fieldIndex("ID"), Qt::Horizontal, "编号");
    tabModel->setHeaderData(tabModel->fieldIndex("PATIENTNAME"), Qt::Horizontal, "患者");
    tabModel->setHeaderData(tabModel->fieldIndex("DOCTORNAME"), Qt::Horizontal, "医生");
    tabModel->setHeaderData(tabModel->fieldIndex("DATE"), Qt::Horizontal, "就诊日期");
    tabModel->setHeaderData(tabModel->fieldIndex("RESULT"), Qt::Horizontal, "就诊");
    tabModel->setHeaderData(tabModel->fieldIndex("DRUG"), Qt::Horizontal, "开药");

    qDebug()<<tabModel;

    selection=new QItemSelectionModel(tabModel);

    pageSize = 5; // 设置每页数据量
    currentPage = 0; // 初始页码为0

    return loadPageData();
}

int IDatabase::addNewMedicalRecord()
{
    //在末尾添加一个记录
    tabModel->insertRow(tabModel->rowCount(),QModelIndex());
    //创建最后一行的MOdelIndex
    QModelIndex curIndex=tabModel->index(tabModel->rowCount()-1,1);

    int curRecNo=curIndex.row();
    QSqlRecord curRec=tabModel->record(curRecNo);

    curRec.setValue("ID",QUuid::createUuid().toString(QUuid::WithBraces));
    curRec.setValue("Date",QDateTime::currentDateTime().toString("yyyy-MM-dd"));

    tabModel->setRecord(curRecNo,curRec);

    return curIndex.row();
}

bool IDatabase::insertReservation(const QString &doctor, const QDate &date, const QTime &time, const QString &patientName, const QString &patientEmail)
{
    if (!database.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(database);
    query.prepare("INSERT INTO reserve (doctor_name, date, time, patient_name, patient_email) "
                  "VALUES (:doctor, :date, :time, :patient_name, :patient_email)");

    query.bindValue(":doctor", doctor);  // 修正占位符为 :doctor
    query.bindValue(":date", date.toString("yyyy-MM-dd"));
    query.bindValue(":time", time.toString("HH:mm:ss"));
    query.bindValue(":patient_name", patientName);
    query.bindValue(":patient_email", patientEmail);

    if (!query.exec()) {
        qDebug() << "Failed to insert reservation:" << query.lastError().text();
        return false;
    }

    return true;
}

bool IDatabase::initDocotorReportModel()
{
    initDatabase();
    filter="";
    tabModel=new QSqlTableModel(this,database);
    tabModel->setTable("doctorreport");
    //设置数据保存方式，按行还是按列
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //设置排序方式
    tabModel->setSort(tabModel->fieldIndex("name"),Qt::AscendingOrder);
    if(!(tabModel->select()))
        return false;

    tableName="doctorreport";
    // 设置列标题（中文）
    tabModel->setHeaderData(tabModel->fieldIndex("ID"), Qt::Horizontal, "编号");
    tabModel->setHeaderData(tabModel->fieldIndex("PATIENTNAME"), Qt::Horizontal, "患者");
    tabModel->setHeaderData(tabModel->fieldIndex("DOCTORNAME"), Qt::Horizontal, "医生");
    tabModel->setHeaderData(tabModel->fieldIndex("CREATETIME"), Qt::Horizontal, "创建时间");
    tabModel->setHeaderData(tabModel->fieldIndex("CONSULTATION"), Qt::Horizontal, "就诊记录");
    tabModel->setHeaderData(tabModel->fieldIndex("TREATMENTEFFECT"), Qt::Horizontal, "治疗效果");
    tabModel->setHeaderData(tabModel->fieldIndex("PATIENTFEEDBACK"), Qt::Horizontal, "病人反馈");


    qDebug()<<tabModel;

    selection=new QItemSelectionModel(tabModel);

    pageSize = 5; // 设置每页数据量
    currentPage = 0; // 初始页码为0

    return loadPageData();
}

int IDatabase::addNewDoctorReport()
{
    //在末尾添加一个记录
    tabModel->insertRow(tabModel->rowCount(),QModelIndex());
    //创建最后一行的MOdelIndex
    QModelIndex curIndex=tabModel->index(tabModel->rowCount()-1,1);

    int curRecNo=curIndex.row();
    QSqlRecord curRec=tabModel->record(curRecNo);

    curRec.setValue("CREATETIME",QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("DOCTORNAME",MasterViw::username);
    curRec.setValue("ID",QUuid::createUuid().toString(QUuid::WithBraces));
    curRec.setValue("DOCTORNAME",MasterViw::username);


    tabModel->setRecord(curRecNo,curRec);

    return curIndex.row();
}

bool IDatabase::initReserveModel()
{
    initDatabase();
    filter="";
    tabModel=new QSqlTableModel(this,database);
    tabModel->setTable("reserve");
    qDebug()<<"reserve";
    //设置数据保存方式，按行还是按列
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //设置排序方式
    tabModel->setSort(tabModel->fieldIndex("name"),Qt::AscendingOrder);
    if(!(tabModel->select()))
        return false;

    tableName="reserve";
    // 设置列标题（中文）
    tabModel->setHeaderData(tabModel->fieldIndex("id"), Qt::Horizontal, "编号");
    tabModel->setHeaderData(tabModel->fieldIndex("patient_name"), Qt::Horizontal, "患者");
    tabModel->setHeaderData(tabModel->fieldIndex("patient_email"), Qt::Horizontal, "患者邮箱");
    tabModel->setHeaderData(tabModel->fieldIndex("doctor_name"), Qt::Horizontal, "医生");
    tabModel->setHeaderData(tabModel->fieldIndex("date"), Qt::Horizontal, "预约日期");
    tabModel->setHeaderData(tabModel->fieldIndex("time"), Qt::Horizontal, "具体时间");
    tabModel->setHeaderData(tabModel->fieldIndex("status"), Qt::Horizontal, "状态");

    qDebug()<<tabModel;

    selection=new QItemSelectionModel(tabModel);

    pageSize = 5; // 设置每页数据量
    currentPage = 0; // 初始页码为0

    return loadPageData();
}


bool IDatabase::search(QString filter)
{
    IDatabase::filter=filter;
    loadPageData();
    currentPage = 0;       // 搜索时从第一页开始显示
    return loadPageData();
}

bool IDatabase::deleteCurrent()
{
    QModelIndex curIndex=selection->currentIndex();
    tabModel->removeRow(curIndex.row());
    tabModel->submitAll();
    tabModel->select();
    loadPageData();
}

bool IDatabase::submitEdit()
{
    return tabModel->submitAll();
}

void IDatabase::revertEdit()
{
    tabModel->revertAll();
}

int IDatabase::addNewPatient()
{
    //在末尾添加一个记录
    tabModel->insertRow(tabModel->rowCount(),QModelIndex());
    //创建最后一行的MOdelIndex
    QModelIndex curIndex=tabModel->index(tabModel->rowCount()-1,1);

    int curRecNo=curIndex.row();
    QSqlRecord curRec=tabModel->record(curRecNo);

    curRec.setValue("CREATEDTIMESTAMP",QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("HEIGHT",170);
    curRec.setValue("WEIGHT",60);
    curRec.setValue("SEX","男");
    curRec.setValue("ID",QUuid::createUuid().toString(QUuid::WithBraces));

    tabModel->setRecord(curRecNo,curRec);

    return curIndex.row();
}




QString IDatabase::userLogin(QString username, QString password)
{
    QSqlQuery query;
    query.prepare("select username,password,type,fullname from user where username= :USER");
    query.bindValue(":USER",username);
    query.exec();
    if(query.first() && query.value("username").isValid()){
        QString passwd=query.value("password").toString();
        if(passwd==password){
            MasterViw::username=query.value("fullname").toString();
            qDebug()<<MasterViw::username;
            return query.value("type").toString();
        }else{
            qDebug()<< "wrongPassword";
            return "loginFailed";
        }
    }else{
        qDebug()<<"no such user";
        return "loginFailed";
    }

}

IDatabase::IDatabase(QObject *parent)
    : QObject{parent}
{
    initDatabase();
}


bool IDatabase::loadPageData() {
    int offset = currentPage * pageSize;

    qDebug() << "filter: " << filter;

    // 检查 filter 是否为空，并构建查询字符串
    QString queryStr;
    if (filter.isEmpty()) {
        queryStr = QString("SELECT * FROM %1 LIMIT %2 OFFSET %3")
                    .arg(tableName)
                   .arg(pageSize)
                   .arg(offset);
    } else {
        queryStr = QString("SELECT * FROM %1 WHERE %2 LIMIT %3 OFFSET %4")
                    .arg(tableName)
                   .arg(filter)
                   .arg(pageSize)
                   .arg(offset);
    }

    // 执行分页查询
    tabModel->setQuery(queryStr, database);

    // 检查查询是否成功
    if (tabModel->lastError().isValid()) {
        qDebug() << "Error in query:" << tabModel->lastError().text();
        return false;
    }

    // 更新 totalRecords
    QSqlQuery countQuery(database);
    QString countQueryStr;
    if (filter.isEmpty()) {
        countQueryStr = QString("SELECT COUNT(*) FROM %1")
                .arg(tableName);
    } else {
        countQueryStr = QString("SELECT COUNT(*) FROM %1 WHERE %2")
                .arg(tableName)
                .arg(filter);
    }

    if (!countQuery.exec(countQueryStr)) {
        qDebug() << "Error in count query:" << countQuery.lastError().text();
        return false;
    }

    if (countQuery.next()) {
        totalRecords = countQuery.value(0).toInt();
        qDebug() << "Total records: " << totalRecords;
    } else {
        qDebug() << "Failed to retrieve total records.";
        return false;
    }

    return true;
}


// 计算最大页数
int IDatabase::getMaxPage() const {
    return (totalRecords + pageSize - 1) / pageSize;  // 向上取整
}

void IDatabase::setPageSize(int size) {
    pageSize = size;
    loadPageData();
}

void IDatabase::setCurrentPage(int page) {
    currentPage = page;
    loadPageData();
}



bool IDatabase::exportData()
{
    // 弹出文件保存对话框，让用户选择路径和文件名
    QString filePath = QFileDialog::getSaveFileName(nullptr, "导出文件", "example", "CSV Files (*.csv);;All Files (*)");

    // 检查用户是否选择了文件路径
    if (filePath.isEmpty()) {
        qDebug() << "No file path selected";
        return false;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing";
        return false;
    }

    // 写入 UTF-8 BOM
    QByteArray bom = QByteArray::fromHex("EFBBBF");
    file.write(bom);

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);  // 设置编码为 UTF-8

    QSqlQuery query(database);
    QString queryStr;

    if (filter.isEmpty()) {
        queryStr = QString("SELECT * FROM %1")
                .arg(tableName);  // 查询整个数据表
    } else {
        queryStr = QString("SELECT * FROM %1 WHERE %2")
                .arg(tableName)
                .arg(filter);
        qDebug() << filter;
    }

    query.prepare(queryStr);
    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        return false;
    }

    // 写入列标题
    QStringList headers;
    for (int i = 0; i < query.record().count(); ++i) {
        headers << query.record().fieldName(i);
    }
    qDebug() << "数量" << query.record().count();
    out << headers.join(",") << "\n";

    // 写入数据行
    while (query.next()) {
        QStringList rowData;
        for (int col = 0; col < query.record().count(); ++col) {
            QString value = query.value(col).toString();
            value.replace('"', "\"\"");  // 处理双引号
            if (value.contains(",")) {
                value = "\"" + value + "\"";  // 如果有逗号，使用双引号包裹
            }
            rowData << value;
        }
        out << rowData.join(",") << "\n";
        qDebug() << rowData;
    }

    file.close();
    qDebug() << "成功";
    return true;
}


bool IDatabase::importData() {
    // 弹出文件选择对话框，让用户选择文件
    QString filePath = QFileDialog::getOpenFileName(nullptr, "导入文件", "", "CSV Files (*.csv);;All Files (*)");

    // 检查用户是否选择了文件路径
    if (filePath.isEmpty()) {
        qDebug() << "No file path selected";
        return false;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading";
        return false;
    }

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);  // 设置编码为 UTF-8

    // 读取列标题
    QString headerLine = in.readLine();
    if (headerLine.isEmpty()) {
        qDebug() << "The file is empty or has no headers";
        return false;
    }
    QStringList headers = headerLine.split(",");

    // 检查表名是否为空
    if (tableName.isEmpty()) {
        qDebug() << "Table name is not set";
        return false;
    }

    // 构造 SQL 插入语句
    QString sql = QString("INSERT INTO %1 (").arg(tableName);
    sql += headers.join(", ");
    sql += ") VALUES (";
    sql += QString("?, ").repeated(headers.size() - 1) + "?";
    sql += ")";

    QSqlQuery query(database);
    query.prepare(sql);

    // 开始处理数据行
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.isEmpty()) {
            continue;  // 跳过空行
        }

        QStringList values = line.split(",");

        // 检查 values 的数量是否与 headers 一致
        if (values.size() != headers.size()) {
            qDebug() << "Row data does not match the number of columns.";
            continue;
        }

        // 绑定每个值到参数化查询
        for (int i = 0; i < values.size(); ++i) {
            query.bindValue(i, values[i].replace("'", "''"));  // 转义单引号
        }

        if (!query.exec()) {
            qDebug() << "Failed to execute query:" << query.lastError().text();
            return false;
        }
    }

    file.close();
    qDebug() << "Import successful";
    return true;
}
