#include "BlockquoteRule.h"
#include <QStringList>

QString BlockquoteRule::apply(const QString &text) const
{
    QStringList lines = text.split('\n');
    QString result;
    bool inQuote = false;

    for (const QString &line : lines) {
        QString trimmed = line.trimmed();

        if (trimmed.startsWith("> ")) {
            if (!inQuote) {
                result += "<blockquote>\n";
                inQuote = true;
            }
            result += trimmed.mid(2) + '\n';
        } else {
            if (inQuote) {
                result += "</blockquote>\n";
                inQuote = false;
            }
            result += line + '\n';
        }
    }

    if (inQuote)
        result += "</blockquote>\n";

    if (result.endsWith('\n'))
        result.chop(1);

    return result;
}
