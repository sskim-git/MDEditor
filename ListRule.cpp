#include "ListRule.h"
#include <QStringList>

QString ListRule::apply(const QString &text) const
{
    // 리스트도 마찬가지
    
    QStringList lines = text.split('\n');
    QString result;
    bool inList = false;

    for (const QString &line : lines) {
        QString trimmed = line.trimmed();

        if (trimmed.startsWith("- ") || trimmed.startsWith("* ")) {
            if (!inList) {
                result += "<ul>\n";
                inList = true;
            }
            result += "<li>" + trimmed.mid(2) + "</li>\n";
        } else {
            if (inList) {
                result += "</ul>\n";
                inList = false;
            }
            result += line + '\n';
        }
    }

    if (inList)
        result += "</ul>\n";

    // 마지막 줄바꿈 제거
    if (result.endsWith('\n'))
        result.chop(1);

    return result;
}
