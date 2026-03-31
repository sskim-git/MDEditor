#ifndef BOLDRULE_H
#define BOLDRULE_H

#include "IMarkdownRule.h"

class BoldRule : public IMarkdownRule
{
public:
    QString apply(const QString &text) const override;
};

#endif // BOLDRULE_H
