#include "welcomeview.h"
#include "ui_welcomeview.h"
#include "QDebug"
#include <QFile>
#include <QDateTime>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

#include <QSqlDatabase>
#include "idatabase.h""


WelcomeView::WelcomeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeView)
{
    qDebug()<<"创建欢迎界面";
    ui->setupUi(this);
}

WelcomeView::~WelcomeView()
{
    qDebug() << "删除欢迎界面";
    delete ui;
}


void WelcomeView::on_btDoctor_clicked()
{
    emit goDoctorView();
}


void WelcomeView::on_btPatient_clicked()
{
    emit goPatientView();
}


void WelcomeView::on_btDrug_clicked()
{
    emit goDrugView();
}


void WelcomeView::on_btMedicalRecord_clicked()
{
    emit goMedicalRecordView();
}


void WelcomeView::on_btReserve_clicked()
{
    emit goReserveView();
}


void WelcomeView::on_btDataAnalysis_clicked()
{
    emit goAnalysisView();
}


#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QMessageBox>
#include <QDebug>

void WelcomeView::on_btSave_clicked()
{
    QString dbFile = "D:/qt/Lab4a.db";
    QString backupDir = "D:/qt/backups/";

    // 确保备份目录存在
    QDir dir(backupDir);
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            QMessageBox::critical(this, "备份失败", "无法创建备份目录：" + backupDir);
            return;
        }
    }

    // 生成备份文件名，包含时间戳
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");
    QString backupFile = backupDir + "Lab4a_backup_" + timestamp + ".db";

    // 检查数据库文件是否存在
    if (!QFile::exists(dbFile)) {
        QMessageBox::warning(this, "备份失败", "数据库文件不存在：" + dbFile);
        return;
    }

    // 执行备份操作
    if (QFile::copy(dbFile, backupFile)) {
        QMessageBox::information(this, "备份成功", "数据库已成功备份到：" + backupFile);
    } else {
        QMessageBox::critical(this, "备份失败", "无法备份数据库文件！");
    }
}



void WelcomeView::on_btResume_clicked()
{
    QString dbFile = "D:/qt/Lab4a.db";
    QString backupDir = "D:/qt/backups/";

    // 打开文件对话框，选择备份文件
    QString backupFile = QFileDialog::getOpenFileName(this, "选择备份文件", backupDir, "Database Files (*.db)");
    if (backupFile.isEmpty()) {
        QMessageBox::warning(this, "恢复取消", "未选择备份文件。");
        return;
    }

    // 检查备份文件是否存在
    if (!QFile::exists(backupFile)) {
        QMessageBox::warning(this, "恢复失败", "备份文件不存在：" + backupFile);
        return;
    }

    // 关闭所有数据库连接
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        db.close();
    }
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);

    // 检查数据库文件是否存在
    if (QFile::exists(dbFile)) {
        // 设置文件可写权限
        if (!QFile::setPermissions(dbFile, QFile::ReadOwner | QFile::WriteOwner)) {
            QMessageBox::critical(this, "权限错误", "无法设置数据库文件的权限：" + dbFile);
            return;
        }

        // 尝试删除现有的数据库文件
        if (!QFile::remove(dbFile)) {
            QMessageBox::critical(this, "恢复失败", "无法删除现有的数据库文件：" + dbFile);
            return;
        }
    }

    // 执行恢复操作
    if (QFile::copy(backupFile, dbFile)) {
        // 设置新数据库文件的权限
        QFile::setPermissions(dbFile, QFile::ReadOwner | QFile::WriteOwner);
        QMessageBox::information(this, "恢复成功", "数据库已成功从备份恢复。");
    } else {
        QMessageBox::critical(this, "恢复失败", "无法复制备份文件到数据库路径！");
    }
}





void WelcomeView::on_btDoctorReport_clicked()
{
    emit goDoctorReportView();
}

