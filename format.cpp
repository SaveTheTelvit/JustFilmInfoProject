#include "format.h"

Format::Format()
{

}

Format::Format(int num)
    : format(num)
{

}

QString Format::toStr() const
{
    switch (format) {
        case 0: return "2D SCOPE";
        case 1: return "2D FLAT";
        case 2: return "3D SCOPE";
        case 3: return "3D FLAT";
        default: return "invalid format";
    }
}

int Format::toInt() const
{
    return format;
}
