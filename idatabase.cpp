#include "idatabase.h"
#include <QUuid>

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
    patientTabModel=new QSqlTableModel(this,database);
    patientTabModel->setTable("patient");
    //设置数据保存方式，按行还是按列
    patientTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //设置排序方式
    patientTabModel->setSort(patientTabModel->fieldIndex("name"),Qt::AscendingOrder);
    if(!(patientTabModel->select()))
        return false;

    thePatientSelection=new QItemSelectionModel(patientTabModel);
    return true;
}

bool IDatabase::searchPatient(QString filter)
{
    patientTabModel->setFilter(filter);
    return patientTabModel->select();
}

bool IDatabase::deleteCurrentPatient()
{
    QModelIndex curIndex=thePatientSelection->currentIndex();
    patientTabModel->removeRow(curIndex.row());
    patientTabModel->submitAll();
    patientTabModel->select();
}

bool IDatabase::submitPatientEdit()
{
    return patientTabModel->submitAll();
}

void IDatabase::revertPatientEdit()
{
    patientTabModel->revertAll();
}

int IDatabase::addNewPatient()
{
    //在末尾添加一个记录
    patientTabModel->insertRow(patientTabModel->rowCount(),QModelIndex());
    //创建最后一行的MOdelIndex
    QModelIndex curIndex=patientTabModel->index(patientTabModel->rowCount()-1,1);

    int curRecNo=curIndex.row();
    QSqlRecord curRec=patientTabModel->record(curRecNo);
    curRec.setValue("CREATEDTIMESTAMP",QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("ID",QUuid::createUuid().toString(QUuid::WithBraces));

    patientTabModel->setRecord(curRecNo,curRec);

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
