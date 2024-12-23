#include "patientreserveview.h"
#include "ui_patientreserveview.h"
#include "idatabase.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include "patientreserveview.h"
#include "ui_patientreserveview.h"
#include "idatabase.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

#include "smtpclient.h"
#include "mimemessage.h"
#include "mimetext.h"

#include <QtCore>




#include <QComboBox>

PatientReserveView::PatientReserveView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientReserveView)
{
    ui->setupUi(this);
    // 初始化时获取所有医生信息
    populateDoctorsComboBox();
}

PatientReserveView::~PatientReserveView()
{
    delete ui;
}

void PatientReserveView::on_btReserve_clicked()
{
    // 获取预约信息
        QString doctor = ui->dbComboDoctor->currentText();
        QDate date = ui->dbEditDate->date();
        QTime time = ui->dbEditTime->time();
        QString patientName = ui->dbEditName->text();
        QString patientEmail = ui->dbEditEmail->text();

        // 调用数据库插入方法
        IDatabase &iDatabase = IDatabase::getInstance();
        if (iDatabase.insertReservation(doctor, date, time, patientName, patientEmail)) {
           QMessageBox::information(this, "预约", "预约提交成功，请等待邮箱通知");
        } else {
            QMessageBox::warning(this, "预约", "预约失败，请稍后再试");
        }

        sendEmailWithQQ();

}


void PatientReserveView::populateDoctorsComboBox()
{
    // 获取当前数据库连接
    QSqlDatabase db = QSqlDatabase::database();  // 默认使用已配置的数据库连接
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return;
    }

    // 创建查询对象
    QSqlQuery query(db);
    query.exec("SELECT name FROM doctor");  // 假设医生表的名字是 doctor，字段名是 name

    // 将查询到的医生名字添加到下拉框
    while (query.next()) {
        QString doctorName = query.value(0).toString();
        ui->dbComboDoctor->addItem(doctorName);  // 将医生名称添加到下拉框
    }

}

void PatientReserveView::sendEmailWithQQ()
{
    // 获取当前选中的医生姓名
    QString doctor = ui->dbComboDoctor->currentText();

    // 获取当前数据库连接
    QSqlDatabase db = QSqlDatabase::database();  // 默认使用已配置的数据库连接
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return;
    }

    QSqlQuery query(db);
    // 执行查询，获取对应医生的邮箱
    query.prepare("SELECT email FROM doctor WHERE name = :name");
    query.bindValue(":name", doctor);

    if (!query.exec() || !query.next()) {
        qDebug() << "Failed to find doctor's email!";
        return;
    }

    QString doctorEmail = query.value("email").toString();  // 获取查询到的邮箱地址

    qDebug()<<"这是邮箱地址" <<doctorEmail;

    if (doctorEmail.isEmpty()) {
        qDebug() << "No email found for doctor!";
        return;
    }

    // 创建邮件
    MimeMessage message;

    // 发件人信息
    EmailAddress sender("1102649355@qq.com", "uskovdqyvpfkbabj");
    message.setSender(sender);

    // 收件人信息使用从数据库查询到的邮箱
    EmailAddress to(doctorEmail, "Recipient's Name");  // 使用查询到的邮箱
    message.addRecipient(to);

    // 邮件主题
    message.setSubject("你有新的预约信息");

    // 邮件正文
    MimeText text;
    text.setText("你有新的预约信息，请上系统查看.\n");

    // 添加邮件正文
    message.addPart(&text);

    // 发送邮件
    SmtpClient smtp("smtp.qq.com", 465, SmtpClient::SslConnection);

    smtp.connectToHost();
    if (!smtp.waitForReadyConnected()) {
        qDebug() << "Failed to connect to host!";
        return;
    }

    smtp.login("1102649355@qq.com", "uskovdqyvpfkbabj");
    if (!smtp.waitForAuthenticated()) {
        qDebug() << "Failed to login!";
        return;
    }

    smtp.sendMail(message);
    if (!smtp.waitForMailSent()) {
        qDebug() << "Failed to send mail!";
        return;
    }

    smtp.quit();
}








