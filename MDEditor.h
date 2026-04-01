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
    MDSyntaxHighlighter *m_highlighter;
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
