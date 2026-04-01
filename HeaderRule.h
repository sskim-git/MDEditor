#ifndef HEADERRULE_H
#define HEADERRULE_H

#include "IMarkdownRule.h"

class HeaderRule : public IMarkdownRule
{
public:
    QString apply(const QString &text) const override;
};

#endif // HEADERRULE_H
