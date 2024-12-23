#include "reserveeditview.h"
#include "ui_reserveeditview.h"
#include "idatabase.h"
#include <QSqlTableModel>
#include <QDebug>

#include "smtpclient.h"
#include "mimemessage.h"
#include "mimetext.h"

#include <QtCore>

#include <QtConcurrent>


ReserveEditView::ReserveEditView(QWidget *parent, int index) :
    QWidget(parent),
    ui(new Ui::ReserveEditView)
{
    ui->setupUi(this);

    dataMapper = new QDataWidgetMapper(this);
    QSqlTableModel *tabModel = IDatabase::getInstance().tabModel;
    dataMapper->setModel(tabModel);

    // 设置提交策略为 ManualSubmit
    dataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    // 绑定控件到模型字段
    dataMapper->addMapping(ui->dbEditName, tabModel->fieldIndex("patient_name"));
    dataMapper->addMapping(ui->dbEditDoctor, tabModel->fieldIndex("doctor_name"));
    dataMapper->addMapping(ui->dbEditDate, tabModel->fieldIndex("date"));
    dataMapper->addMapping(ui->dbEditTime, tabModel->fieldIndex("time"));
    dataMapper->addMapping(ui->dbEditEmail, tabModel->fieldIndex("patient_email"));
    dataMapper->addMapping(ui->dbComboStatus, tabModel->fieldIndex("status"));


    // 设置当前索引
    dataMapper->setCurrentIndex(index);

}

ReserveEditView::~ReserveEditView()
{
    delete ui;
}

void ReserveEditView::on_btCancel_clicked()
{
    // 撤销更改
    IDatabase::getInstance().tabModel->revertAll();

    emit goPreviousView();
}



void ReserveEditView::on_btSave_clicked() {
    dataMapper->submit();

    if (!IDatabase::getInstance().tabModel->submitAll()) {
        qDebug() << "Failed to submit data:" << IDatabase::getInstance().tabModel->lastError().text();
    } else {
        qDebug() << "Data saved successfully!";
    }

    qDebug() << "预约信息的状态为" << ui->dbComboStatus->currentText();

    // 异步执行发送邮件
    if (ui->dbComboStatus->currentText() == "Confirmed") {
        QtConcurrent::run([=]() { sendEmailWithQQ("预约成功，请按时前往"); });
    } else if (ui->dbComboStatus->currentText() == "Cancel") {
        QtConcurrent::run([=]() { sendEmailWithQQ("预约失败，请重新预约"); });
    }

    IDatabase::getInstance().loadPageData();
    emit goPreviousView();
}

void ReserveEditView::sendEmailWithQQ(const QString &msg)
{
    QString patientEmail = ui->dbEditEmail->text();

    qDebug()<<"这是邮箱地址" <<patientEmail;

    if (patientEmail.isEmpty()) {
        qDebug() << "No email found for doctor!";
        return;
    }

    // 创建邮件
    MimeMessage message;

    // 发件人信息
    EmailAddress sender("1102649355@qq.com", "uskovdqyvpfkbabj");
    message.setSender(sender);

    // 收件人信息使用从数据库查询到的邮箱
    EmailAddress to(patientEmail, "Recipient's Name");  // 使用查询到的邮箱
    message.addRecipient(to);

    // 邮件主题
    message.setSubject("你有新的预约信息");

    // 邮件正文
    MimeText text;
    text.setText(msg);

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






