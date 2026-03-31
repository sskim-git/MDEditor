#include "MDEditor.h"
#include "MDSyntaxHighlighter.h"

#include <QPainter>
#include <QTextBlock>
#include <QTextCursor>

MDEditor::MDEditor(QWidget *parent)
    : QPlainTextEdit(parent)
    , m_lineNumberArea(new LineNumberArea(this))
{
    // Qt는 보통 생성할때 UI에 관한 부분을 설정합니다.
    // 일관성있는 자신만의 코드 스타일이 중요

    // 모노스페이스 폰트 설정
    QFont font("Consolas", 11); 
    font.setStyleHint(QFont::Monospace);
    setFont(font);

    setTabStopDistance(fontMetrics().horizontalAdvance(' ') * 4); // 이런 부분은. 아까 setCentralWidget처럼 지금 class의 부모인 MDEditor의 부모 QWidget의 함수이기도하고, 자체 함수이기도 함
    setLineWrapMode(QPlainTextEdit::NoWrap);

    // Qt의 특징. SIGNAL과 SLOT 부분입니다. Event 발생이라 보면되고 신호와 신호를 받는 함수라고 보면됩니다.

    connect(this, &QPlainTextEdit::blockCountChanged, // 앞에 this는 지금 여기에 있는 QPlainTextEdit를 가리키기 위함입니다. 뒤에 this는 MDEditor도 여기에 있는 거라는 내용입니다.
            this, &MDEditor::updateLineNumberAreaWidth); // QPlainTextEdit 라는 텍스트 입력창에서 발생하는 SIGNAL을 MDEditor의 SLOT에 연결하는 부분
    connect(this, &QPlainTextEdit::updateRequest, // 텍스트 입력창에서 업데이트 요청 시그날이 있으면, 에디터의 라인넘버영역을 업데이트하라
            this, &MDEditor::updateLineNumberArea);
    connect(this, &QPlainTextEdit::cursorPositionChanged, // 커서 위치가 바껴면~ 현재 라인에 하이라이트하는 곳을 한번 체크해봐라는 뜻
            this, &MDEditor::highlightCurrentLine); // 이런식으로 시그날 발생하면 처리해야될 함수에 연결을 합니다. 상세한 내용은 구현부분에 가면 정의되어있음.

    updateLineNumberAreaWidth(0); // 아래의 정의된 함수.
    highlightCurrentLine();

    m_highlighter = new MDSyntaxHighlighter(document());
}

int MDEditor::lineNumberAreaWidth() const // 자릿수를 세는 함수
{
    int digits = 1;
    int max = qMax(1, blockCount()); 
    while (max >= 10) { // 1~9줄이면 1칸으로 표시, 10~99면 2칸으로 표시. 이런식으로 계산
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * (digits + 1); //고정 너비로 해도되지만 동적으로 너비를 계산해서 줄수에 맞춰서 너비를 재조정하기 위함
    return space; // 나중에 차이점 확인
}

void MDEditor::updateLineNumberAreaWidth(int /*newBlockCount*/) // 마찬가지로 마진 설정하는 부분
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0); // 영역이 업데이트 되거나.
}

void MDEditor::updateLineNumberArea(const QRect &rect, int dy) // 영역의 크기를 재설정 하는 부분.
{
    if (dy)
        m_lineNumberArea->scroll(0, dy);
    else
        m_lineNumberArea->update(0, rect.y(), m_lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void MDEditor::resizeEvent(QResizeEvent *event) //윈도우 자체가 재조정 될때 영역을 재조정하는 부분.
{
    QPlainTextEdit::resizeEvent(event); //QT나 윈도우 프로그램은 크기가 변동할때 UI부분을 새로 그립니다. 그거에 해당하는 부분을 다 처리하도록 이벤트를 연결해서. 내가 원하는 모양으로 설정합니다.

    QRect cr = contentsRect();
    m_lineNumberArea->setGeometry(
        QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height())); // 윈도우가 재조정될때
}

void MDEditor::highlightCurrentLine() //커서가 있는 라인의 색상을 변경, 실행해서 글자를 입력하는 라인이 노란색으로 보이는 처리를 여기서함, 따라서 
{ // 따라서 위에서 cursorPositionChanged를 연결한 것. 어디가 편집 라인인지 볼수 있도록. 편집기에서는 가독성을 위해 중요
    QList<QTextEdit::ExtraSelection> extraSelections; 

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;
        QColor lineColor = QColor(Qt::yellow).lighter(180);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void MDEditor::lineNumberAreaPaintEvent(QPaintEvent *event) // 에디터 좌측에 텍스트가 입력된 부분의 줄 번호를 입력하는 부분. 여기에서 줄이 10개 넘어가거나 100개 넘어가면
{ // 왼쪽 영역을 재조정해줘야 글자가 들어갈 크기가 되는 부분. lineNumberAreaWidth 가 필요함
     // 해당 부분은 PaintEvent로 LineNumberArea::paintEvent가 호출될때 연결됨
    QPainter painter(m_lineNumberArea);
    painter.fillRect(event->rect(), QColor(240, 240, 240));

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(QColor(130, 130, 130));
            painter.drawText(0, top, m_lineNumberArea->width() - 2,
                             fontMetrics().height(), Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}

void MDEditor::insertMarkdown(const QString &before, const QString &after)
{
    QTextCursor cursor = textCursor();
    QString selected = cursor.selectedText();

    cursor.beginEditBlock();
    if (selected.isEmpty()) {
        cursor.insertText(before + after);
        cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, after.length());
    } else {
        cursor.insertText(before + selected + after);
    }
    cursor.endEditBlock();

    setTextCursor(cursor);
    setFocus();
}

void MDEditor::insertAtLineStart(const QString &prefix)
{
    QTextCursor cursor = textCursor();

    cursor.beginEditBlock();
    cursor.movePosition(QTextCursor::StartOfBlock);
    cursor.insertText(prefix);
    cursor.endEditBlock();

    setTextCursor(cursor);
    setFocus();
}

void MDEditor::insertBlock(const QString &block)
{
    QTextCursor cursor = textCursor();

    cursor.beginEditBlock();
    if (!cursor.atBlockStart())
        cursor.insertText("\n");
    cursor.insertText(block);
    cursor.endEditBlock();

    setTextCursor(cursor);
    setFocus();
}
