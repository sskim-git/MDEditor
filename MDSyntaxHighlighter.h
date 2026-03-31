#ifndef MDSYNTAXHIGHLIGHTER_H
#define MDSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>

class MDSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    explicit MDSyntaxHighlighter(QTextDocument *parent = nullptr);

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };

    QList<HighlightRule> m_rules;
    QRegularExpression m_codeBlockStart;
    QRegularExpression m_codeBlockEnd;
    QTextCharFormat m_codeBlockFormat;
};

#endif // MDSYNTAXHIGHLIGHTER_H
