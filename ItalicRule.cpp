#include "ItalicRule.h"
#include <QRegularExpression>

// 기울기는, *글짜* 로 표현하면 기울어지게
QString ItalicRule::apply(const QString &text) const
{
    QString result = text;

    // *기울임* 또는 _기울임_ (Bold 처리 이후에 적용되어야 함) .. *** 글짜 *** 이경우 두꺼워진 글짜가 기울여진다는 내용입니다.
    result.replace(QRegularExpression("\\*(.+?)\\*"), "<i>\\1</i>");
    result.replace(QRegularExpression("(?<!_)_(.+?)_(?!_)"), "<i>\\1</i>");
    // <i> </i> 가 기울임 표현
    

    return result;
}
