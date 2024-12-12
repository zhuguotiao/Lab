#include "masterviw.h"
#include "ui_masterviw.h"
#include <QDebug>
#include "idatabase.h"

MasterViw::MasterViw(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MasterViw)
{
    ui->setupUi(this);

    // 设置登录页面的边框边框
    // this->setWindowFlag(Qt::FramelessWindowHint);

    //初始化跳转到登录页面
    goLoginView();

    IDatabase::getInstance();

}

MasterViw::~MasterViw()
{
    delete ui;
}

void MasterViw::goLoginView()
{
    qDebug() << "跳转到登录页面";

    loginView=new LoginView(this);
    //把页面加进去
    pushWidgetToStackView(loginView);

    //等待接受登录成功的信号
    //这是新版本的
    connect(loginView, &LoginView::loginSuccess, this, &MasterViw::goWelcomeView);;
}

void MasterViw::goWelcomeView(const QString &type)
{
    qDebug() << "跳转到欢迎页面";
    qDebug() << type;

    welcomeView=new WelcomeView(this);
    pushWidgetToStackView(welcomeView);

    // 动态查找并隐藏按钮
       if (type == "1") {
           QPushButton *btDrug = welcomeView->findChild<QPushButton *>("btDrug");
           if (btDrug) btDrug->hide();
       } else if (type == "2") {
           QPushButton *btPatient = welcomeView->findChild<QPushButton *>("btPatient");
           QPushButton *btMedicalRecord = welcomeView->findChild<QPushButton *>("btMedicalRecord");
           if (btPatient) btPatient->hide();
           if (btMedicalRecord) btMedicalRecord->hide();
       }

    connect(welcomeView, &WelcomeView::goDoctorView, this, &MasterViw::goDoctorView);;
    connect(welcomeView, &WelcomeView::goPatientView, this, &MasterViw::goPatientView);;
    connect(welcomeView, &WelcomeView::goDrugView, this, &MasterViw::goDrugView);;
    connect(welcomeView, &WelcomeView::goMedicalRecordView, this, &MasterViw::goMedicalRecordView);;

}

//医生相关操作
void MasterViw::goDoctorView()
{
    qDebug() << "跳转到医生页面";

    doctorView=new DoctorView(this);
    pushWidgetToStackView(doctorView);
    connect(doctorView, &DoctorView::goDoctorEditView, this, &MasterViw::goDoctorEditView);;

}

void MasterViw::goDoctorEditView(int rowNo)
{
    qDebug() << "跳转到医生编辑页面";

    doctorEditView=new DoctorEditView(this,rowNo);
    pushWidgetToStackView(doctorEditView);

    connect(doctorEditView, &DoctorEditView::goPreviousView, this, &MasterViw::goPreviousView);

}


//患者相关操作
void MasterViw::goPatientEditView(int rowNo)
{
    qDebug() << "跳转到患者编辑页面";

    patientEditView=new PatientEditView(this,rowNo);
    pushWidgetToStackView(patientEditView);

    connect(patientEditView, &PatientEditView::goPreviousView, this, &MasterViw::goPreviousView);;

}

void MasterViw::goPatientView()
{
    qDebug() << "跳转到患者页面";

    patientView=new PatientView(this);
    pushWidgetToStackView(patientView);;

    connect(patientView, &PatientView::goPatientEditView, this, &MasterViw::goPatientEditView);;

}

void MasterViw::goMedicalRecordView()
{
    qDebug() << "跳转到就诊记录页面";

    medicalRecordView=new MedicalRecordView(this);
    pushWidgetToStackView(medicalRecordView);

    connect(medicalRecordView, &MedicalRecordView::goMedicalRecordEditView, this, &MasterViw::goMedicalRecordEditView);;

}

void MasterViw::goMedicalRecordEditView(int rowNo)
{
    qDebug() << "跳转到药品编辑页面";

    medicalRecordEditView=new MedicalRecordEditView(this,rowNo);
    pushWidgetToStackView(medicalRecordEditView);

    connect(medicalRecordEditView, &MedicalRecordEditView::goPreviousView, this, &MasterViw::goPreviousView);
}

void MasterViw::goDrugView()
{
    qDebug() << "跳转到药品管理页面";

    drugView=new DrugView(this);
    pushWidgetToStackView(drugView);

    connect(drugView, &DrugView::goDrugEditView, this, &MasterViw::goDrugEditView);;

}

void MasterViw::goDrugEditView(int rowNo)
{
    qDebug() << "跳转到药品编辑页面";

    drugEditView=new DrugEditView(this,rowNo);
    pushWidgetToStackView(drugEditView);

    connect(drugEditView, &DrugEditView::goPreviousView, this, &MasterViw::goPreviousView);

}


//通用操作
void MasterViw::goPreviousView()
{
    qDebug() << "跳转到前一个";
    int count=ui->stackedWidget->count();

    if(count>1){
        ui->stackedWidget->setCurrentIndex(count-2);
        ui->labelTitle->setText(ui->stackedWidget->currentWidget()->windowTitle());

        //获取当前的页面如何把他删掉
        QWidget *widget=ui->stackedWidget->widget(count-1);
        ui->stackedWidget->removeWidget(widget);
        delete widget;
    }

}

void MasterViw::pushWidgetToStackView(QWidget *widget)
{
    //把页面加进去
    ui->stackedWidget->addWidget(widget);
    //显示最新的页面
    int count=ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(count-1);
    ui->labelTitle->setText(widget->windowTitle());
}


void MasterViw::on_btBack_clicked()
{
    goPreviousView();
}


void MasterViw::on_stackedWidget_currentChanged(int arg1)
{
    int count=ui->stackedWidget->count();
    if(count>1)
        ui->btBack->setEnabled(true);
    else
        ui->btBack->setEnabled(false);

    QString title=ui->stackedWidget->currentWidget()->windowTitle();

    if(title=="欢迎"){
        ui->btLogout->setEnabled(true);
        ui->btBack->setEnabled(false);
    }else{
        ui->btLogout->setEnabled(false);
    }
}


void MasterViw::on_btLogout_clicked()
{
    goPreviousView();
}

