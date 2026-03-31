#include "MainWindow.h"
#include "MDEditor.h"
#include "MDParser.h"
#include "MDPreviewer.h"
#include <QSplitter>
#include <QMenuBar>
#include <QToolBar>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    setupMenuBar();
    setupToolBar();

    m_parser = new MDParser(this);

    connect(m_editor, &QPlainTextEdit::textChanged, this, &MainWindow::onTextChanged);

    setWindowTitle(tr("마크다운 에디터")); // 윈도우 타이틀
    resize(1200, 700); // 시작시 윈도우 사이즈, 필요시 resize를 통해 조정, 해상도 반영 등
}

void MainWindow::setupUI()
{
    m_splitter = new QSplitter(Qt::Horizontal, this); // 화면을 2개로 나누기 위해 사용

    m_editor = new MDEditor(m_splitter); // MDEdtor.cpp 클래스를 생성. 부모를 스플리터로 지정. 메모리 관리 측면
    m_previewer = new MDPreviewer(m_splitter); // MDPreviewer.cpp 클래스를 생성.. 부모를 스플리터로 지정

    m_splitter->addWidget(m_editor); // 스플리터에 넣음. 모양적인 측면
    m_splitter->addWidget(m_previewer); // 스플리터에 넣음
    m_splitter->setSizes({600, 600}); // 스플리터 사이즈 조정, 반반

    setCentralWidget(m_splitter); //아래와 동일

    // this->setCentralWidget(m_splitter); //setCentralWidget 함수는 QMainWinodow의 함수로 가운데 위젯을 설정하는 함수. this로 지정하면 자신의 함수가 나옴
}

void MainWindow::setupMenuBar() // 메뉴바 설정
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File")); // 메뉴바 생성.

    QAction *newAction = fileMenu->addAction(tr("&New"), this, &MainWindow::onNewFile); // 액션 생성, 액션은 말그대로 행위를 만드는 것인데. 함수를 연결한다고 보면됨
    newAction->setShortcut(QKeySequence::New); // 단축키 지정

    QAction *openAction = fileMenu->addAction(tr("&Open..."), this, &MainWindow::onOpenFile);
    openAction->setShortcut(QKeySequence::Open);

    QAction *saveAction = fileMenu->addAction(tr("&Save"), this, &MainWindow::onSaveFile);
    saveAction->setShortcut(QKeySequence::Save);

    fileMenu->addSeparator(); //메뉴의 분리 바. 보통 종료 위에 분리함

    QAction *exitAction = fileMenu->addAction(tr("E&xit"), this, &QWidget::close); // 종료 버튼
    exitAction->setShortcut(QKeySequence::Quit);
}

void MainWindow::setupToolBar()
{
    QToolBar *toolbar = addToolBar(tr("Formatting"));
    toolbar->setMovable(false);
    toolbar->setIconSize(QSize(18, 18));

    // 실행 취소 / 다시 실행
    toolbar->addAction(tr("↩ Undo"), m_editor, &QPlainTextEdit::undo)->setShortcut(QKeySequence::Undo);
    toolbar->addAction(tr("↪ Redo"), m_editor, &QPlainTextEdit::redo)->setShortcut(QKeySequence::Redo);

    toolbar->addSeparator();

    // 제목 H1 ~ H3
    toolbar->addAction(tr("H1"), [this]() { m_editor->insertAtLineStart("# "); });
    toolbar->addAction(tr("H2"), [this]() { m_editor->insertAtLineStart("## "); });
    toolbar->addAction(tr("H3"), [this]() { m_editor->insertAtLineStart("### "); });

    toolbar->addSeparator();

    // 굵게, 기울임, 취소선, 코드
    toolbar->addAction(tr("B"), [this]() { m_editor->insertMarkdown("**", "**"); });
    toolbar->addAction(tr("I"), [this]() { m_editor->insertMarkdown("*", "*"); });
    toolbar->addAction(tr("S"), [this]() { m_editor->insertMarkdown("~~", "~~"); });
    toolbar->addAction(tr("<>"), [this]() { m_editor->insertMarkdown("`", "`"); });

    toolbar->addSeparator();

    // 링크, 이미지
    toolbar->addAction(tr("Link"), [this]() { m_editor->insertMarkdown("[", "](url)"); });
    toolbar->addAction(tr("Img"), [this]() { m_editor->insertMarkdown("![", "](image_url)"); });

    // 목록
    toolbar->addAction(tr("UL"), [this]() { m_editor->insertAtLineStart("- "); });
    toolbar->addAction(tr("OL"), [this]() { m_editor->insertAtLineStart("1. "); });

    toolbar->addSeparator();

    // 인용, 수평선, 코드블록
    toolbar->addAction(tr("\" Quote"), [this]() { m_editor->insertAtLineStart("> "); });
    toolbar->addAction(tr("— HR"), [this]() { m_editor->insertBlock("\n---\n"); });
    toolbar->addAction(tr("Code Block"), [this]() { m_editor->insertMarkdown("```\n", "\n```"); });

    // 툴바 버튼 스타일
    toolbar->setStyleSheet(
        "QToolBar { background: #f5f0e8; border-bottom: 1px solid #ddd; padding: 2px; spacing: 2px; }"
        "QToolButton { background: transparent; border: 1px solid transparent; border-radius: 3px;"
        "  padding: 3px 6px; font-size: 12px; font-weight: bold; color: #555; }"
        "QToolButton:hover { background: #e8e0d0; border: 1px solid #ccc; }"
        "QToolButton:pressed { background: #ddd; }"
    );
}

void MainWindow::onNewFile() // 위에서 생성한 New에 해당하는 함수의 구현 부분
{
    m_editor->clear(); // 새로 만들때 에디터의 내용을 지움
    m_previewer->setHtmlContent(QString()); // 우측 미리보기도 지움
    m_currentFilePath.clear(); // 파일 경로도 초기화
    setWindowTitle(tr("마크다운 에디터")); // 윈도우 타이틀을 여기서 다시 지정함. 보통 파일을 열때 파일 경로를 윈도우 타이틀에 넣어줄때 사용하므로 초기화 해주는 것. 위에서 조정했기 때문에 수정. 나중에 경로 붙일때도 수정
}

void MainWindow::onOpenFile() // 파일을 열때 
{
    QString filePath = QFileDialog::getOpenFileName( // 파일 열기 다이알로그. 간편하게 윈도우에서 열기 위해 구현이 되어있음. 
        this, tr("Open Markdown File"), QString(), // 다이얼로그의 제목창
        tr("Markdown Files (*.md *.markdown);;All Files (*)")); // 파일 필터 지정. 

        // 해당 Qt함수들의 파라미터의 사용은 QtCreator에서 하면 자동완성과, 설명이 보임. 지금은 Live Share를 위해 code를 사용할뿐 QtCreator를 사용하여 작업하는게 맞음

    if (filePath.isEmpty()) // 새로 선택한 파일이 없을 경우 파일 열기 취소, 해당 처리는 파일 열기에서 취소로 눌린것도 여기서 리턴됨
        return;

    QFile file(filePath); // 마찬가지로 파일이 올바른지 체크함
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"),
                             tr("Cannot open file: %1").arg(file.errorString()));
        return;
    }

    m_editor->setPlainText(QString::fromUtf8(file.readAll())); // 파일에서 읽어온 값(UTF8형태)을 스트링으로 변환한뒤 에디터에 글자를 넣어줌
    m_currentFilePath = filePath; // 파일 패스를 지정해주고. 
    setWindowTitle(tr("마크다운 에디터 - %1").arg(filePath)); // 아까 말했던 파일경로의 타이틀 지정을 여기서 해줌. 바꿧으니 여기도 바꿔줘야. 일관성 유지
}

void MainWindow::onSaveFile() // 파일 저장
{
    if (m_currentFilePath.isEmpty()) { // 열기와 마찬가지, 다만 저장할때는 저장하는 이름을 적음, 
        m_currentFilePath = QFileDialog::getSaveFileName(
            this, tr("Save Markdown File"), QString(),
            tr("Markdown Files (*.md *.markdown);;All Files (*)"));
    }

    // 읽기와 마찬가지
    if (m_currentFilePath.isEmpty())
        return;

    QFile file(m_currentFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"),
                             tr("Cannot save file: %1").arg(file.errorString()));
        return;
    }

    // 실제 파일에 쓰는 부분,
    file.write(m_editor->toPlainText().toUtf8());

    setWindowTitle(tr("마크다운 에디터 - %1").arg(m_currentFilePath)); // 덮어쓰거나 했을 수 있어서 지금의 파일 경로로 타이틀 바꿈
}

void MainWindow::onTextChanged()
{
    QString text = m_editor->toPlainText();
    QString html = m_parser->parse(text);
    m_previewer->setHtmlContent(html);
}
