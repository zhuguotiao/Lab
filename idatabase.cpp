#include "idatabase.h"
#include <QUuid>
#include <QFile>
#include <QTextStream>
#include <QSqlRecord>
#include <QFileDialog>


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
    tabModel=new QSqlTableModel(this,database);
    tabModel->setTable("patient");
    //设置数据保存方式，按行还是按列
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //设置排序方式
    tabModel->setSort(tabModel->fieldIndex("name"),Qt::AscendingOrder);
    if(!(tabModel->select()))
        return false;


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

bool IDatabase::searchPatient(QString filter)
{
    IDatabase::filter=filter;
    loadPageData();
    currentPage = 0;       // 搜索时从第一页开始显示
    return loadPageData();
}

bool IDatabase::deleteCurrentPatient()
{
    QModelIndex curIndex=selection->currentIndex();
    tabModel->removeRow(curIndex.row());
    tabModel->submitAll();
    tabModel->select();
}

bool IDatabase::submitPatientEdit()
{
    return tabModel->submitAll();
}

void IDatabase::revertPatientEdit()
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
    query.prepare("select username,password,type from user where username= :USER");
    query.bindValue(":USER",username);
    query.exec();
    if(query.first() && query.value("username").isValid()){
        QString passwd=query.value("password").toString();
        if(passwd==password){
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
        queryStr = QString("SELECT * FROM patient LIMIT %1 OFFSET %2")
                   .arg(pageSize)
                   .arg(offset);
    } else {
        queryStr = QString("SELECT * FROM patient WHERE %1 LIMIT %2 OFFSET %3")
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
        countQueryStr = "SELECT COUNT(*) FROM patient";
    } else {
        countQueryStr = QString("SELECT COUNT(*) FROM patient WHERE %1").arg(filter);
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



#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

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
        queryStr = "SELECT * FROM patient";  // 查询整个数据表
    } else {
        queryStr = QString("SELECT * FROM patient WHERE %1").arg(filter);
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


bool IDatabase::importData()
{
    return true;
}
