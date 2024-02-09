#ifndef FORMAT_H
#define FORMAT_H

#include <QString>

class Format
{
public:
    Format();
    Format(int num);
    QString toStr() const;
    int toInt() const;
private:
    int format = 99;
};

#endif // FORMAT_H
