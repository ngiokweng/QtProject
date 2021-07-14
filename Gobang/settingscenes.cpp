#include "settingscenes.h"
#include "ui_settingscenes.h"
#include "mainwindow.h"

SettingScenes::SettingScenes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingScenes)
{
    ui->setupUi(this);
    MainWindow* w;
    connect(ui->btn_ok,&QPushButton::clicked,[=](){
        if(ui->radioButton->isChecked()){
            emit this->playWithAI();
        }else if(ui->radioButton_2->isChecked()){
            emit this->playWithMan();
        }else{
            return;
        }
        this->close();
        w->show();
    });
}

SettingScenes::~SettingScenes()
{
    delete ui;
}
