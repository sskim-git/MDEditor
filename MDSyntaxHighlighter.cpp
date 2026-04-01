#include "MDSyntaxHighlighter.h"

MDSyntaxHighlighter::MDSyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    // QSyntaxHighlighter 클래스는, parent로 받은 값을 시그날에 연결을 하는 부분이 있습니다. Document를 연결해서 생성을하면.
    // 자동으로 SIGNAL, SLOT이 연결된다고 보시면됩니다.

    // 만약 parent에 연결될 값을 안넣었다고 치면
    // 어제 SIGNAL SLOT연결하듯이.

    connect(this, &QPlainTextEdit::signal명, this, &QSyntaxHighlighter::slot명); // 이런식으로 연결을 해줘야하는데
    // QSyntaxHighlighter를 사용하는 용도가 정해져있어서. 생성할때 넣어주면 연결하는 부분이 이미 구현되어있기때문에
    // parent로 넣어준다 입니다.

    HighlightRule rule;

    // 제목 (# ~ ######)
    QTextCharFormat headerFormat;
    headerFormat.setForeground(QColor(0, 100, 180));
    headerFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression("^#{1,6}\\s+.*$");
    rule.format = headerFormat;
    m_rules.append(rule);

    // 굵게 (**text** 또는 __text__)
    QTextCharFormat boldFormat;
    boldFormat.setFontWeight(QFont::Bold);
    boldFormat.setForeground(QColor(180, 80, 0));
    rule.pattern = QRegularExpression("\\*\\*.+?\\*\\*|__.+?__");
    rule.format = boldFormat;
    m_rules.append(rule);

    // 기울임 (*text* 또는 _text_)
    QTextCharFormat italicFormat;
    italicFormat.setFontItalic(true);
    italicFormat.setForeground(QColor(140, 100, 0));
    rule.pattern = QRegularExpression("(?<!\\*)\\*(?!\\*).+?(?<!\\*)\\*(?!\\*)|(?<!_)_(?!_).+?(?<!_)_(?!_)");
    rule.format = italicFormat;
    m_rules.append(rule);

    // 인라인 코드 (`code`)
    QTextCharFormat inlineCodeFormat;
    inlineCodeFormat.setForeground(QColor(200, 50, 50));
    inlineCodeFormat.setBackground(QColor(245, 245, 245));
    inlineCodeFormat.setFontFamilies({"Consolas", "monospace"});
    rule.pattern = QRegularExpression("`[^`]+`");
    rule.format = inlineCodeFormat;
    m_rules.append(rule);

    // 링크 [text](url)
    QTextCharFormat linkFormat;
    linkFormat.setForeground(QColor(0, 120, 200));
    linkFormat.setFontUnderline(true);
    rule.pattern = QRegularExpression("\\[.+?\\]\\(.+?\\)");
    rule.format = linkFormat;
    m_rules.append(rule);

    // 이미지 ![alt](url)
    QTextCharFormat imageFormat;
    imageFormat.setForeground(QColor(80, 160, 80));
    imageFormat.setFontUnderline(true);
    rule.pattern = QRegularExpression("!\\[.*?\\]\\(.+?\\)");
    rule.format = imageFormat;
    m_rules.append(rule);

    // 목록 (- 또는 * 또는 숫자.)
    QTextCharFormat listFormat;
    listFormat.setForeground(QColor(180, 0, 180));
    rule.pattern = QRegularExpression("^\\s*[-*]\\s+|^\\s*\\d+\\.\\s+");
    rule.format = listFormat;
    m_rules.append(rule);

    // 인용 (>)
    QTextCharFormat blockquoteFormat;
    blockquoteFormat.setForeground(QColor(100, 140, 100));
    blockquoteFormat.setFontItalic(true);
    rule.pattern = QRegularExpression("^>\\s+.*$");
    rule.format = blockquoteFormat;
    m_rules.append(rule);

    // 수평선 (---, ***, ___)
    QTextCharFormat hrFormat;
    hrFormat.setForeground(QColor(150, 150, 150));
    rule.pattern = QRegularExpression("^(---+|\\*\\*\\*+|___+)\\s*$");
    rule.format = hrFormat;
    m_rules.append(rule);

    // 코드 블록 (``` ... ```)
    m_codeBlockStart = QRegularExpression("^```.*$");
    m_codeBlockEnd = QRegularExpression("^```\\s*$");
    m_codeBlockFormat.setForeground(QColor(200, 50, 50));
    m_codeBlockFormat.setBackground(QColor(245, 245, 245));
    m_codeBlockFormat.setFontFamilies({"Consolas", "monospace"});
}

void MDSyntaxHighlighter::highlightBlock(const QString &text)
{
    // 일반 규칙 적용
    for (const HighlightRule &rule : m_rules) { // 이런식으로 리스트에 넣은 다음에 for문에서 돌리기 쉽기 때문에 리스트를 씁니다.
        QRegularExpressionMatchIterator it = rule.pattern.globalMatch(text);
        while (it.hasNext()) {
            QRegularExpressionMatch match = it.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    // 쌍을 처리하고 싶은데 만약에 이렇게 구조체를 안쓰고 각각 리스트를 써버리면
     // 이런 식으로 for문을 두번 돌려야하는데, 이건 사실 의도에도 맞지도 않고, 오류를 발생할 여지도 많으며, 지금 처리하고자 하는 내용을 처리하기 매우 힘듭니다.
    for (const QRegularExpression &RE : listRE) { 
        // 인덱스를 찾음
    }

    for (const QTextCharFormat &format : listFormat) { 
        // 인덱스를 찾음
    }

    // 찾은 인덱스를 가지고 

            while (it.hasNext()) {
            QRegularExpressionMatch match = it.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
        // 에 해당하는 처리를 해줘야함. 으로 매우 비효율 적이 됩니다.


    // 코드 블록 (여러 줄) 처리
    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1) {
        QRegularExpressionMatch startMatch = m_codeBlockStart.match(text);
        if (startMatch.hasMatch()) {
            startIndex = startMatch.capturedStart();
            setFormat(startIndex, text.length() - startIndex, m_codeBlockFormat);
            setCurrentBlockState(1);
            return;
        }
    } else {
        QRegularExpressionMatch endMatch = m_codeBlockEnd.match(text);
        if (endMatch.hasMatch()) {
            setFormat(0, endMatch.capturedEnd(), m_codeBlockFormat);
            setCurrentBlockState(0);
        } else {
            setFormat(0, text.length(), m_codeBlockFormat);
            setCurrentBlockState(1);
        }
    }
}
