#include "LinkRule.h"
#include <QRegularExpression>

QString LinkRule::apply(const QString &text) const
{
    QString result = text;

    result.replace(QRegularExpression("!\\[(.*)\\]\\((.+?)\\)"),
                   "<img src=\"\\2\" alt=\"\\1\" style=\"max-width:100%;\">");

    result.replace(QRegularExpression("\\[(.+?)\\]\\((.+?)\\)"),
                   "<a href=\"\\2\">\\1</a>");

    return result;
}
