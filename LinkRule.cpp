#include "LinkRule.h"
#include <QRegularExpression>

QString LinkRule::apply(const QString &text) const
{
    QString result = text;

    // 이미지: ![alt](url) — 링크보다 먼저 처리
    result.replace(QRegularExpression("!\\[(.*)\\]\\((.+?)\\)"),
                   "<img src=\"\\2\" alt=\"\\1\" style=\"max-width:100%;\">");

    // 링크: [text](url)
    result.replace(QRegularExpression("\\[(.+?)\\]\\((.+?)\\)"),
                   "<a href=\"\\2\">\\1</a>");

    return result;
}
