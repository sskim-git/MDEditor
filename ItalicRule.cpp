#include "ItalicRule.h"
#include <QRegularExpression>

QString ItalicRule::apply(const QString &text) const
{
    QString result = text;

    result.replace(QRegularExpression("\\*(.+?)\\*"), "<i>\\1</i>");
    result.replace(QRegularExpression("(?<!_)_(.+?)_(?!_)"), "<i>\\1</i>");

    return result;
}
