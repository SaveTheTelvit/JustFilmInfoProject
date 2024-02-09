#include "filmtime.h"

FTime operator+(const FTime& t1, const FTime& t2)
{
    return FTime(t1.duration() + t2.duration());
}

FTime operator+=(FTime& t1, const FTime& t2)
{
    t1.seconds += t2.seconds;
    t1.minutes += t2.minutes;
    t1.hours += t2.hours;
    t1.validate();
    return t1;
}

FTime::FTime()
{

}

FTime::FTime(const QString str)
{
    toTime(str);
}

FTime::FTime(int s)
    : seconds(s)
{
    validate();
}

FTime::FTime(int m, int s)
    : minutes(m)
    , seconds(s)
{
  validate();
}

FTime::FTime(int h, int m, int s)
  : hours(h)
  , minutes(m)
  , seconds(s)
{
    validate();
}

int FTime::duration() const
{
    return hours * 3600 + minutes * 60 + seconds;
}

QString FTime::toStr() const
{
    return timeFormat(hours, minutes, seconds);
}

void FTime::toTime(QString str)
{
    str = TextCorrector::maxSimplefied(str, ":");
    QVector<int> vec;
    int pos = 0, qPos = 0;
    while((pos = str.indexOf(':', qPos)) != -1) {
        vec.push_back(str.mid(qPos, pos - qPos).toInt());
        qPos = pos + 1;
    }
    if (qPos < str.size()) vec.push_back(str.mid(qPos).toInt());
    QVector<int>::iterator it = vec.begin();
    switch (vec.size()) {
        default:
        case 3:
            hours = *it;
            it++;
            [[fallthrough]];
        case 2:
            minutes = *it;
            it++;
            [[fallthrough]];
        case 1:
            seconds = *it;
        break;
        case 0:
        break;
    }
    validate();
}

QString FTime::timeFormat(int sec)
{
    return timeFormat(sec / 3600, (sec  % 3600) / 60, sec % 60);
}

QString FTime::timeFormat(int h, int m, int s)
{
    QString str = "";
    if (h > 0) {
        str += QString::number(h) + ':';
        if (m < 10) str += '0';
    }
    str += QString::number(m) + ':';
    if (s < 10) str += '0';
    str += QString::number(s);
    return str;
}

void FTime::validate()
{
    if (seconds > 59) {
        minutes += seconds / 60;
        seconds %= 60;
    }
    if (minutes > 59) {
        hours += minutes / 60;
        minutes %= 60;
    }
}
