#ifndef ITALICRULE_H
#define ITALICRULE_H

#include "IMarkdownRule.h"
// 같은 개념입니다.
// 기울기 적용하는 부분~
class ItalicRule : public IMarkdownRule
{
public:
    QString apply(const QString &text) const override;
};

#endif // ITALICRULE_H
