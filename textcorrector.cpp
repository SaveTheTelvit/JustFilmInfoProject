#include "textcorrector.h"

QString TextCorrector::noFirstLastSym(const QString &str)
{
    QString edit = str;
    if (str.size() != 0) {
        if (!str[str.size() - 1].isDigit()) edit = edit.remove(str.size() - 1, 1);
        if (!str[0].isDigit()) edit = edit.remove(0,1);
    }
    return edit;
}

QString TextCorrector::noDuplicateSym(const QString &str)
{
    QString edit = "";
    QChar lastChar(0);
    for (int i = 0; i < str.size(); i++) {
        if (str[i] != lastChar || str[i].isDigit()) edit.append(str[i]);
        lastChar = str[i];
    }
    return edit;
}

QString TextCorrector::justDigitSym(const QString &str, const QString symbols)
{
    QString edit = "";
    for (int i = 0; i < str.size(); i++) {
        if (str[i].isDigit()) {
            edit += str[i];
        } else {
            for (int j = 0; j < symbols.size(); j++) {
                if (str[i] == symbols[j]) {
                    edit += str[i];
                    break;
                }
            }
        }
    }
    return edit;
}

QString TextCorrector::maxSimplefied(const QString str, const QString symbols)
{
    return noFirstLastSym(noDuplicateSym(justDigitSym(str, symbols)));
}
