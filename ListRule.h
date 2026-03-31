#ifndef LISTRULE_H
#define LISTRULE_H

#include "IMarkdownRule.h"

class ListRule : public IMarkdownRule
{
public:
    QString apply(const QString &text) const override;
};

#endif // LISTRULE_H
