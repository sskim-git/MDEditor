#ifndef HORIZONTALRULE_H
#define HORIZONTALRULE_H

#include "IMarkdownRule.h"

class HorizontalRule : public IMarkdownRule
{
public:
    QString apply(const QString &text) const override;
};

#endif // HORIZONTALRULE_H
