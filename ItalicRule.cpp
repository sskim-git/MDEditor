#include "ItalicRule.h"
#include <QRegularExpression>

QString ItalicRule::apply(const QString &text) const
{
    QString result = text;

    // *기울임* 또는 _기울임_ (Bold 처리 이후에 적용되어야 함)
    result.replace(QRegularExpression("\\*(.+?)\\*"), "<i>\\1</i>");
    result.replace(QRegularExpression("(?<!_)_(.+?)_(?!_)"), "<i>\\1</i>");

    return result;
}
