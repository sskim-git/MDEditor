#include "HeaderRule.h"
#include <QRegularExpression>

// 즉 이 함수는 우리가 editor창에 입력한 글짜중에 #, ##, ###으로 시작하는 글자는 이렇게 바꾸자라고 정의한 함수입니다.
// 위에 단축키로 H1, H2, H3을 클릭하면 자동으로 #, ##, ### 이 들어가게 되어있습니다. 그건 나중에 다른 부분에서 구현되어있음.
// 이 함수는 단순하게 찾아서 바꾸는 부분임

// 방금 해더의 cpp파일이니까 방금 선언한 함수에 대해 구현이 되어있습니다. 
QString HeaderRule::apply(const QString &text) const // 선언한대로. 스트링 타입으로 반환하는 그런 내용입니다.
{
    QString result = text; // 이 함수를 콜하면서 매개변수로 text를 넣어준걸로 Qstring에 넣어준다음.

    // h6 ~ h1 순서로 처리 (h1부터 하면 ## 도 h1으로 잡힘)
    for (int level = 6; level >= 1; --level) { // 문자가 어떤 방식으로 되어있는지 파악하는 부분입니다.
        QString pattern = QString("^(#{%1})\\s+(.+)$").arg(level); // 내용을 살펴보면 ^로 시작은 줄의 시작을 의미를 하고 #{%1} #이 몇개인지. s+(.+)$나머지 텍스트는 어떤건지. 
        QString replacement = QString("<h%1>\\2</h%1>").arg(level); // 이런식으로 문자에서 뽑아내서.
        result.replace(QRegularExpression(pattern, QRegularExpression::MultilineOption), replacement); // 여기서 대체한다.
        // 이런 부분인데 이런건 외우는게 아니고 참조해서 붙여넣는거라 의미만 알면됩니다.
    }

    // 텍스트를 받아서 해더 룰이니까. 값을 찐하게 표시? 하는 형태로 바꿔주는 부분입니다.
    // Qt에서 실행해보면 # << 으로 시작하는 글짜를 찐하게 바꿔주는 내용입니다.
    // 숨고 챗에 캡쳐올렸습니다.
     // #으로 시작하는 것은 #, ##, ### 의 갯수에 따라서. 보이는 형태를 replace해서 바꿔준다라고 보몁됩니다.
     // 저 정규식의 경우는 외우는게 아니라 인터넷으로 찾거나 하는거고, 마크다운은 정의된 언어이기 때문에. 표현방법이 나와있습니다.


    return result;
}
