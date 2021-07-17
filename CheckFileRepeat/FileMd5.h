#ifndef FILEMD5_H
#define FILEMD5_H

#include <QObject>
#include <QHash>



class FileMd5 : public QObject
{
    Q_OBJECT
public:
    explicit FileMd5(QObject *parent = nullptr);

signals:
    void gotDumplate(const QHash<QByteArray,QStringList> &dumplates);
    void process(int current, int total);

public slots:
    void checkDumplate(const QString &path);


private:
    QStringList getFiles(const QString& path);
    QByteArray getFileMd5(const QString &fileName);



};

#endif // FILEMD5_H
