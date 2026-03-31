#include "BoldRule.h"
#include <QRegularExpression>

QString BoldRule::apply(const QString &text) const
{
    QString result = text;

    // **굵게** 또는 __굵게__
    result.replace(QRegularExpression("\\*\\*(.+?)\\*\\*"), "<b>\\1</b>");
    result.replace(QRegularExpression("__(.+?)__"), "<b>\\1</b>");

    return result;
}
