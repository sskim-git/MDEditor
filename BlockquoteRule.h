#ifndef BLOCKQUOTERULE_H
#define BLOCKQUOTERULE_H

#include "IMarkdownRule.h"

class BlockquoteRule : public IMarkdownRule
{
public:
    QString apply(const QString &text) const override;
};

#endif // BLOCKQUOTERULE_H
