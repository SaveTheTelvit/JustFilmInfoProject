#ifndef TEXTCORRECTOR_H
#define TEXTCORRECTOR_H

#include <QString>

class TextCorrector
{
public:
    static QString noFirstLastSym(const QString& str);
    static QString noDuplicateSym(const QString& str);
    static QString justDigitSym(const QString& str, const QString symbols);
    static QString maxSimplefied(const QString str, const QString symbols);
};

#endif // TEXTCORRECTOR_H
