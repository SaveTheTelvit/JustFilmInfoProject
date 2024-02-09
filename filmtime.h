#ifndef FTIME_H
#define FTIME_H

#include <QString>
#include <QVector>

#include "textcorrector.h"

class FTime
{
public:
    FTime();
    FTime(const QString str);
    FTime(int s);
    FTime(int m, int s);
    FTime(int h, int m, int s);
    int duration() const;
    QString toStr() const;
    static QString timeFormat(int sec);
    static QString timeFormat(int h, int m, int s);
    friend FTime operator+(const FTime& t1, const FTime& t2);
    friend FTime operator+=(FTime& t1, const FTime& t2);
private:
    void toTime(QString str);
    void validate();
    int hours = 0, minutes = 0, seconds = 0;
};

#endif // FTIME_H
