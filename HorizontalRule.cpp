#include "HorizontalRule.h"
#include <QRegularExpression>

QString HorizontalRule::apply(const QString &text) const
{
    QString result = text;

    // ---, ***, ___ (3개 이상)
    result.replace(QRegularExpression("^(---+|\\*\\*\\*+|___+)\\s*$",
                                      QRegularExpression::MultilineOption),
                   "<hr>");

    return result;
}
