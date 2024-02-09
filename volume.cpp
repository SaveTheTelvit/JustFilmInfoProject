#include "volume.h"

Volume::Volume()
{

}

Volume::Volume(float vol)
    :volume(vol)
{
    validate();
}

Volume::Volume(int vol)
    :volume(vol)
{
    volume /= 10;
    validate();
}

Volume::Volume(const QString str)
{
    toVolume(str);
    if (str.indexOf('.') == -1) volume /= 10;
    validate();
}

QString Volume::toStr() const
{
    QString str = QString::number(volume);
    if (str.indexOf('.') == -1) str.append(".0");
    return str;
}

int Volume::toInt() const
{
    return static_cast<int>(volume * 10);
}

void Volume::toVolume(QString str)
{
    volume = TextCorrector::maxSimplefied(str, ".").toFloat();
}

void Volume::validate()
{
    if (volume < 0.0f) volume = 0.0f;
    volume = static_cast<float>(static_cast<int>(volume * 10)) / 10;
}
