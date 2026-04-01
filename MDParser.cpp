#include "MDParser.h"
#include "IMarkdownRule.h"
#include <QRegularExpression>
#include "CodeBlockRule.h"
#include "HeaderRule.h"
#include "BoldRule.h"
#include "ItalicRule.h"
#include "LinkRule.h"
#include "BlockquoteRule.h"
#include "HorizontalRule.h"
#include "ListRule.h"

MDParser::MDParser(QObject *parent)
    : QObject(parent)
{
    m_rules.append(new CodeBlockRule());
    m_rules.append(new HorizontalRule());
    m_rules.append(new HeaderRule());
    m_rules.append(new BlockquoteRule());
    m_rules.append(new BoldRule());
    m_rules.append(new ItalicRule());
    m_rules.append(new LinkRule());
    m_rules.append(new ListRule());
}

MDParser::~MDParser()
{
    qDeleteAll(m_rules);
}

QString MDParser::parse(const QString &text) const
{
    QString result = text;

    for (const IMarkdownRule *rule : m_rules) {
        result = rule->apply(result);
    }

    result.replace(QRegularExpression("\n\n"), "</p><p>");
    result.replace(QRegularExpression("\n"), "<br>");
    result = "<p>" + result + "</p>";

    return result;
}
