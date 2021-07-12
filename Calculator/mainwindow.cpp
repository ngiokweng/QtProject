#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //基本設置
    ui->label->setStyleSheet("QLabel { background-color : white;font-size:40px ;}");
    ui->label->setAlignment(Qt::AlignRight|Qt::AlignCenter);
    this->setFixedSize(QSize(487,594));
    this->setWindowTitle("只是一個普通計數器");

    //連接數字0-9
    connect(ui->btn_0,&QPushButton::clicked,[=](){
        QString str=ui->label->text();
        str.push_back("0");
        ui->label->setText(str);
    });
    connect(ui->btn_1,&QPushButton::clicked,[=](){
        QString str=ui->label->text()+"1";
        ui->label->setText(str);

    });
    connect(ui->btn_2,&QPushButton::clicked,[=](){
        QString str=ui->label->text()+"2";
        ui->label->setText(str);

    });
    connect(ui->btn_3,&QPushButton::clicked,[=](){
        QString str=ui->label->text()+"3";
        ui->label->setText(str);

    });
    connect(ui->btn_4,&QPushButton::clicked,[=](){
        QString str=ui->label->text()+"4";
        ui->label->setText(str);

    });
    connect(ui->btn_5,&QPushButton::clicked,[=](){
        QString str=ui->label->text()+"5";
        ui->label->setText(str);

    });
    connect(ui->btn_6,&QPushButton::clicked,[=](){
        QString str=ui->label->text()+"6";
        ui->label->setText(str);

    });
    connect(ui->btn_7,&QPushButton::clicked,[=](){
        QString str=ui->label->text()+"7";
        ui->label->setText(str);

    });
    connect(ui->btn_8,&QPushButton::clicked,[=](){
        QString str=ui->label->text()+"8";
        ui->label->setText(str);

    });
    connect(ui->btn_9,&QPushButton::clicked,[=](){
        QString str=ui->label->text()+"9";
        ui->label->setText(str);

    });
    //連接 .
    connect(ui->btn_point,&QPushButton::clicked,[=](){
        QString oldStr = ui->label->text();
        //限制只能有一個.
        int pointNum = oldStr.count(".");
        if(oldStr == ""||pointNum==1){
            return;
        }
        QString newStr=oldStr+".";
        ui->label->setText(newStr);


    });
    //連接<-
    connect(ui->btn_back,&QPushButton::clicked,[=](){
        QString oldStr = ui->label->text();
        if(oldStr == ""){
            return;
        }
        QString newStr = oldStr.remove(-1,1);
        ui->label->setText(newStr);

    });
    //連接 +
    connect(ui->btn_add,&QPushButton::clicked,[=](){
        if(ui->label->text()==""){
            return;
        }
        double value = ui->label->text().toDouble();
        Value val("+",value);
        this->allValueAndOperator.push_back(val);
        ui->label->setText("");
    });
    //連接 -
    connect(ui->btn_minus,&QPushButton::clicked,[=](){
        if(ui->label->text()==""){
            return;
        }
        double value = ui->label->text().toDouble();
        Value val("-",value);
        this->allValueAndOperator.push_back(val);
        ui->label->setText("");
    });
    //連接 *
    connect(ui->btn_multiply,&QPushButton::clicked,[=](){
        if(ui->label->text()==""){
            return;
        }
        double value = ui->label->text().toDouble();
        Value val("*",value);
        this->allValueAndOperator.push_back(val);
        ui->label->setText("");
    });
    //連接 /
    connect(ui->btn_divided,&QPushButton::clicked,[=](){
        if(ui->label->text()==""){
            return;
        }
        double value = ui->label->text().toDouble();
        Value val("/",value);
        this->allValueAndOperator.push_back(val);
        ui->label->setText("");
    });
     //連接 =
    connect(ui->btn_equals,&QPushButton::clicked,[=](){
        if(ui->label->text()==""){
            return;
        }
        double value = ui->label->text().toDouble();
        Value val("!",value);
        this->allValueAndOperator.push_back(val);

        QVector<Value>::iterator it = this->allValueAndOperator.begin();
        double res = it->value;
        for(;it!=this->allValueAndOperator.end();it++){

           double val = (it+1)->value;

           if(it->oper=="+"){
               res+=val;

           }else if(it->oper=="-"){
               res-=val;

           }else if(it->oper=="*"){
               res*=val;

           }else if(it->oper=="/"){
               res/=val;

           }
           if((it+1)->oper=="!")break;
        }
        ui->label->setNum(res);
        this->allValueAndOperator.clear();
    });
    //連接 clear
    connect(ui->btn_clear,&QPushButton::clicked,[=](){
        this->allValueAndOperator.clear();
        ui->label->setText("");
    });
    //連接 退出
    connect(ui->btn_close,&QPushButton::clicked,[=](){
        this->close();
    });
    //連接 +/-
    connect(ui->btn_strains,&QPushButton::clicked,[=](){
        if(ui->label->text()==""){
            return;
        }
        double val=ui->label->text().toDouble();
        val=-val;

        ui->label->setText(QString::number(val));
    });






}

MainWindow::~MainWindow()
{
    delete ui;
}

