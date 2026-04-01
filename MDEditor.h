#ifndef MDEDITOR_H
#define MDEDITOR_H

#include <QPlainTextEdit>

class LineNumberArea;
class MDSyntaxHighlighter;

class MDEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit MDEditor(QWidget *parent = nullptr);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth() const;

    // 포맷팅 삽입 함수
    void insertMarkdown(const QString &before, const QString &after);
    void insertAtLineStart(const QString &prefix);
    void insertBlock(const QString &block);

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &rect, int dy);
    void highlightCurrentLine();

private:
    LineNumberArea *m_lineNumberArea;
    MDSyntaxHighlighter *m_highlighter; // 방금 설명한 에디터에서 하이라이트 주기위해 기능을 정의한 클래스를 내부 변수로 선언
};

class LineNumberArea : public QWidget
{
public:
    explicit LineNumberArea(MDEditor *editor)
        : QWidget(editor), m_editor(editor) {}

    QSize sizeHint() const override
    {
        return QSize(m_editor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        m_editor->lineNumberAreaPaintEvent(event);
    }

private:
    MDEditor *m_editor;
};

#endif // MDEDITOR_H
