#ifndef STRUCTS_H
#define STRUCTS_H

#include <QString>

#include "filmtime.h"
#include "format.h"
#include "volume.h"

struct TlrInfo {
    int id;
    QString name;
    FTime duration;
    Volume volume;
};

struct FilmInfo {
    int id;
    Format format;
    QString name;
    FTime duration;
    FTime titleTime;
    Volume volume;
    QVector<TlrInfo> tlrs;
};

#endif // STRUCTS_H
