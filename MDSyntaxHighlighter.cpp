#include "MDSyntaxHighlighter.h"

MDSyntaxHighlighter::MDSyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
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
    for (const HighlightRule &rule : m_rules) {
        QRegularExpressionMatchIterator it = rule.pattern.globalMatch(text);
        while (it.hasNext()) {
            QRegularExpressionMatch match = it.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

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
