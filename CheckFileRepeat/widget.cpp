#include "widget.h"
#include "ui_widget.h"
#include <QDir>
#include <QFile>
#include <QCryptographicHash>
#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    thread.start();
    md5.moveToThread(&thread);

    //跨線程傳遞自定義類型/模板時，要使用下列方法先注冊，否則會報錯
    qRegisterMetaType<QHash<QByteArray,QStringList>>("QHash<QByteArray,QStringList>");

    /*
     * 按下按鈕->發送&Widget::checkDumplate( 信號 )
     * &Widget::checkDumplate( 信號 )與&FileMd5::checkDumplate( 槽 )相連接
     * &FileMd5::checkDumplate( 槽 )發送 &FileMd5::gotDumplate( 信號 )
     * &FileMd5::gotDumplate( 信號 )與&Widget::onGotDumplate( 槽 )相連接
     * 最後：&Widget::onGotDumplate( 槽 )將重複文件的hash添加到listWidget中
    */
    connect(this,&Widget::checkDumplate,&md5,&FileMd5::checkDumplate);
    connect(&md5,&FileMd5::gotDumplate,this,&Widget::onGotDumplate);
    connect(&md5,&FileMd5::process,this,&Widget::onProcess);


}

Widget::~Widget()
{
    //關閉線程
    thread.exit();
    thread.wait();
    delete ui;
}

void Widget::closeEvent(QCloseEvent *event)
{
    if(!isDone){
        QMessageBox::warning(this,"警告","文件加載中，請物關閉窗口");
        //忽略這個事件，當前窗口不會關閉
         event->ignore();
    }else{
        //接收這個事件，當前窗口會關閉
        event->accept();
    }


}


void Widget::on_pushButton_clicked()
{
    ui->progressBar->setValue(0);
    ui->listWidget->clear();

    //判斷是否有文件正在加載
    if(!isDone){
       QMessageBox::warning(this,"警告","年輕人別太心急，我跑不動了");
       return;
    }
    isDone = false;

    //選擇目錄
    QString path = QFileDialog::getExistingDirectory(this,"Choose Dir",".");
    ui->lineEdit->setText(path);

    emit checkDumplate(path);
}

void Widget::onGotDumplate(const QHash<QByteArray, QStringList> &dumplates)
{
    this->dumplates = dumplates;
    for(QHash<QByteArray,QStringList>::const_iterator it = dumplates.begin(); it != dumplates.end(); it++){

        if(it.value().count()>1){
            ui->listWidget->addItem(it.key());
        }
    }
    if(ui->listWidget->count()==0){
        ui->listWidget->addItem("沒有重複的文件");
    }

}

void Widget::onProcess(int current, int total)
{
    ui->progressBar->setValue(current);
    ui->progressBar->setMaximum(total);

    if(current == total){
        isDone = true;
    }
}

void Widget::on_listWidget_currentTextChanged(const QString &currentText)
{
    ui->listWidget_2->clear();

    QStringList fileList = this->dumplates[currentText.toLocal8Bit()];
    ui->listWidget_2->addItems(fileList);
}
