#ifndef VALUE_H
#define VALUE_H
#include <QString>

class Value
{
public:
    Value(QString oper,double value);
    QString oper;
    double value;
};

#endif // VALUE_H
