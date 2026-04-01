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

// 생성자는 이 클랙스가 생성될때 호출됩니다. 
MDParser::MDParser(QObject *parent)
    : QObject(parent)
{
    // 순서가 중요!
    // 1) 코드 블록을 먼저 처리 (안의 내용이 다른 규칙에 영향받지 않도록)
    // 2) 헤더 처리
    // 3) Bold → Italic 순서 (**가 *보다 먼저 매칭되어야 함) << 이부분때문에 순서가 중요
    // 4) 리스트 처리
    m_rules.append(new CodeBlockRule()); // 룰 리스트에 아까 쭉 둘러본 함수들의 룰을 추가합니다.
    m_rules.append(new HorizontalRule()); 
    m_rules.append(new HeaderRule());
    m_rules.append(new BlockquoteRule()); 
    m_rules.append(new BoldRule()); // 왜냐면 선처리되는 부분이라서 그렇습니다.
    m_rules.append(new ItalicRule());
    m_rules.append(new LinkRule());
    m_rules.append(new ListRule());
    // 여기에 append하면 바로 적용됩니다.
}

MDParser::~MDParser()
{
    qDeleteAll(m_rules);
}

QString MDParser::parse(const QString &text) const
{
    QString result = text;

    for (const IMarkdownRule *rule : m_rules) { // 여기서 추가된 룰을 처음부터 쭉 둘러보면서, 적용을 합니다.
        result = rule->apply(result); // 이부분을 보면 클래스가 다 다른데, IMarkdownR ule 부모를 잡아서. 같은 함수로 호출했습니다.
    } // 이게 상속의 장점이고, 가상함수로 알차게 만든 부분을 통해 쉽게 한줄로 처리했습니다.
    // 만약 이부분을 상속을 안받고. 별개로 다 apply를 구현했다면 아래와 같이 표현됩니다.

    // 빈 줄을 <p> 태그로 감싸기 (단락 구분)
    result.replace(QRegularExpression("\n\n"), "</p><p>"); // \n\n으로 표현된 부분을 단락으로 묶어주고
    result.replace(QRegularExpression("\n"), "<br>"); // 띄어쓰기 넣어주고
    result = "<p>" + result + "</p>"; // 그래서 들어온 글짜를 마지막으로 단락으로 묶어주고

    return result; // 반환합니다.

    // 여기서 왜 이렇게 만드는게 중요한 이유가 또 잇습니다.
    // 만약 새로운 문법이 추가로 정의되면
    // h, cpp파일 만들고, 추가하고.

    // 일부분의 수정이 전체 구조에 영향을 미치지않는구조로 
    // Strategy Pattern 이라고 합니다. .. 알고리즘 규칙을 캡슐화 해서, 교체 가능하게 만드는 패턴 입니다.
    // 만약 전담하는 부분이 틀리면 그 클랙스부분만 수정하면 해결됩니다.
    // 확장에는 열린 구조, 수정에는 닫힌 구조라해서. 개방 폐쇄 원칙 OCP라고 하기도 합니다.

}
