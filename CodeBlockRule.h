#ifndef CODEBLOCKRULE_H
#define CODEBLOCKRULE_H

#include "IMarkdownRule.h"

class CodeBlockRule : public IMarkdownRule
{
public:
    QString apply(const QString &text) const override;
};

#endif // CODEBLOCKRULE_H
