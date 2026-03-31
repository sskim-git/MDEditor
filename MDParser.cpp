#include "MDParser.h"
#include "IMarkdownRule.h"
#include <QRegularExpression>
#include "CodeBlockRule.h"
#include "HeaderRule.h"
#include "BoldRule.h"
#include "ItalicRule.h"
#include "ListRule.h"

MDParser::MDParser(QObject *parent)
    : QObject(parent)
{
    // 순서가 중요!
    // 1) 코드 블록을 먼저 처리 (안의 내용이 다른 규칙에 영향받지 않도록)
    // 2) 헤더 처리
    // 3) Bold → Italic 순서 (**가 *보다 먼저 매칭되어야 함)
    // 4) 리스트 처리
    m_rules.append(new CodeBlockRule());
    m_rules.append(new HeaderRule());
    m_rules.append(new BoldRule());
    m_rules.append(new ItalicRule());
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

    // 빈 줄을 <p> 태그로 감싸기 (단락 구분)
    result.replace(QRegularExpression("\n\n"), "</p><p>");
    result.replace(QRegularExpression("\n"), "<br>");
    result = "<p>" + result + "</p>";

    return result;
}
