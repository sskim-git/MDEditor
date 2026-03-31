#include "HeaderRule.h"
#include <QRegularExpression>

QString HeaderRule::apply(const QString &text) const
{
    QString result = text;

    // h6 ~ h1 순서로 처리 (h1부터 하면 ## 도 h1으로 잡힘)
    for (int level = 6; level >= 1; --level) {
        QString pattern = QString("^(#{%1})\\s+(.+)$").arg(level);
        QString replacement = QString("<h%1>\\2</h%1>").arg(level);
        result.replace(QRegularExpression(pattern, QRegularExpression::MultilineOption), replacement);
    }

    return result;
}
