#include "FileMd5.h"
#include <QFileInfo>
#include <QDir>
#include <QCryptographicHash>
#include <QApplication>
#include <QDebug>

FileMd5::FileMd5(QObject *parent) : QObject(parent)
{

}

void FileMd5::checkDumplate(const QString &path)
{
    //寫代碼檢測文件重複
    QHash<QByteArray,QStringList> ret;

    QStringList files = getFiles(path);

    for(int i = 0; i < files.count(); i++){
        QString fileName = files.at(i);
        QByteArray md5 = getFileMd5(fileName);

        ret[md5].append(fileName);

        emit process(i+1,files.count());
    }

    emit gotDumplate(ret);
}

QStringList FileMd5::getFiles(const QString &path)
{
    QStringList ret;

    QDir dir(path);
    //.表示當前目錄，..表示上一級目錄
    //entryInfoList：返回目錄中所有文件和目錄的QFileInfo對象列表
    QFileInfoList infoList = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    for(int i=0; i < infoList.count(); i++){
        QFileInfo info = infoList.at(i);
        if(info.isDir()){
            QString subDir = info.absoluteFilePath();
            QStringList files = getFiles(subDir);
            ret.append(files);
        }else{
            QString fileName = info.absoluteFilePath();
            ret.append(fileName);
        }
    }
    return ret;
}

QByteArray FileMd5::getFileMd5(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)){
        return QByteArray();
    }

    QCryptographicHash hash(QCryptographicHash::Md5);
    while(!file.atEnd()){
        QByteArray content = file.read(100 * 1024 * 1024); //一次讀取100MB的內容
        hash.addData(content); //將content的數據添加到密碼散列
        qApp->processEvents(); //防止整個程序卡住(作用不大)
    }
    QByteArray md5 = hash.result().toHex(); //獲取最終的哈希值
    file.close();
    return md5;
}
