#include "loginview.h"
#include "ui_loginview.h"
#include "QDebug"
#include "idatabase.h"

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
    QString status=IDatabase::getInstance().userLogin(ui->inputUsername->text(),ui->inputPasswd->text());
    if(status!="loginFailed"){
        emit loginSuccess(status);
        qDebug()<<"发送信号成功";
    }else{
        emit LoginFailed();
    }

}

