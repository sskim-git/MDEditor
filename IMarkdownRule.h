#ifndef IMARKDOWNRULE_H // 이거는 정의하는건데, #if not def 의 줄임말로, 만약 IMARKDOWNRULE_H 명칭으로 정의가 되지 안았다면
#define IMARKDOWNRULE_H // IMARKDOWNRULE_H 이름으로 정의를 하겠다 라는겐데. 이 밑에 있는 내용들이 IMARKDOWNRULE_H라는 이름으로 정의를 하는거예요

// 보통 헤더파일을 생성하면 자동으로 붙게 되는데. 파일명으로 저렇게 만들면, 파일명이 중복되지 않는한 엉킬일이 없습니다. // 파일 명을 강제로 바꾸는 경우는 바꿔줘야 하는 경우도 있겠죠

#include <QString> // 마찬가지로 Qt 함수의 Qstirng도 사용한다고 해야. 밑에서 

// 방금 Include한 해더파일인데, 가상함수입니다.
class IMarkdownRule
{
public:
    virtual ~IMarkdownRule() = default; 
    virtual QString apply(const QString &text) const = 0; // 여기서 리턴 값으로 쓸수있어요. 가상함수 쪽인데 이건 나중에 보도록 하고. // 본체없는 정의만 있음
    // 가상 함수를 정의하는 곳은 이 함수를 상속받은 클래스는 꼭 이 함수를 재 정의해서 사용하라는 표시예요 // 마크다운 룰을 만들때 apply 함수를 구현하는 것을 빼먹지 마라! 이런뜻으로 보면됩니다.
};

#endif // IMARKDOWNRULE_H
