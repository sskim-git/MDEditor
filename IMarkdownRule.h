#ifndef IMARKDOWNRULE_H
#define IMARKDOWNRULE_H

#include <QString>

class IMarkdownRule
{
public:
    virtual ~IMarkdownRule() = default;
    virtual QString apply(const QString &text) const = 0;
};

#endif // IMARKDOWNRULE_H
