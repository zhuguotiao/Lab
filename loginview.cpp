#include "loginview.h"
#include "ui_loginview.h"
#include "QDebug"
#include "idatabase.h"
#include "QMessageBox"  // 引入QMessageBox

LoginView::LoginView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginView)
{
    ui->setupUi(this);
}

LoginView::~LoginView()
{
    delete ui;
}

void LoginView::on_btSignIn_clicked()
{
    QString status = IDatabase::getInstance().userLogin(ui->inputUsername->text(), ui->inputPasswd->text());
    if (status != "loginFailed") {
        emit loginSuccess(status);
        qDebug() << "发送信号成功";
    } else {
        // 登录失败时弹出提示框
        QMessageBox::warning(this, "登录失败", "用户名或密码错误", QMessageBox::Ok);
        emit LoginFailed();
    }
}

void LoginView::on_btReserve_clicked()
{
    emit reserve();
}
