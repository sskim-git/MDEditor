#ifndef ITALICRULE_H
#define ITALICRULE_H

#include "IMarkdownRule.h"

class ItalicRule : public IMarkdownRule
{
public:
    QString apply(const QString &text) const override;
};

#endif // ITALICRULE_H
