#ifndef LINKRULE_H
#define LINKRULE_H

#include "IMarkdownRule.h"

class LinkRule : public IMarkdownRule
{
public:
    QString apply(const QString &text) const override;
};

#endif // LINKRULE_H
