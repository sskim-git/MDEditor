#ifndef HEADERRULE_H
#define HEADERRULE_H

#include "IMarkdownRule.h" // 이런 해더만 존재하는 경우가 있습니다. //정의만 해도되는경우

// 클래스 정의
class HeaderRule : public IMarkdownRule // 부모 클래스 // 돌아와서. 이 해더는 마크다운 룰 클래스 방금. 해더를 상속 받았습니다.
{
public: // 공개. public은 이 함수를 다른 클래스에서 호출해야할 때 씁니다.
    QString apply(const QString &text) const override; // 스트링 타입 반환하는 함수 선언 // 그래서 여기서 이제 apply를 재정의합니다.

protected: // 예를 들면, Protected는 내 클래스, 즉 HeaderRule를 또 상속 받은 자식 클래스에서 사용할 수 있어요
    //QString apply2(const QString &text) const override; // 스트링 타입 반환하는 함수 선언

private:
    //QString apply3(const QString &text) const override; // 이거는 나만 쓰는것,

    // 함수는 해더에 정의를 해야하는데 오픈하는 범위라고 생각하면 됩니다.
    // public을 함으로써 다른 클래스에서 호출하게 해주고
    // 함부로 호출하지 못하게 하는건 private로 보호한다고 보면되요

    
};

#endif // HEADERRULE_H
