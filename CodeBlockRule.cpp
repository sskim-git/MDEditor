#include "CodeBlockRule.h"
#include <QRegularExpression>
#include <QStringList>

QString CodeBlockRule::apply(const QString &text) const
{
    QString result = text;

    // ``` 코드 블록 ``` (여러 줄)
    result.replace(
        QRegularExpression("```\\w*\\n(.*?)```", QRegularExpression::DotMatchesEverythingOption),
        "<pre><code>\\1</code></pre>");

    // `인라인 코드`
    result.replace(QRegularExpression("`([^`]+)`"), "<code>\\1</code>");

    return result;
}
