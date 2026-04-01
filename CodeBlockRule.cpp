#include "CodeBlockRule.h"
#include <QRegularExpression>
#include <QStringList>

QString CodeBlockRule::apply(const QString &text) const
{
    QString result = text;

    result.replace(
        QRegularExpression("```\\w*\\n(.*?)```", QRegularExpression::DotMatchesEverythingOption),
        "<pre><code>\\1</code></pre>");

    result.replace(QRegularExpression("`([^`]+)`"), "<code>\\1</code>");

    return result;
}
