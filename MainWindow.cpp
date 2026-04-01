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

    setWindowTitle(tr("마크다운 에디터"));
    resize(1200, 700);
}

void MainWindow::setupUI()
{
    m_splitter = new QSplitter(Qt::Horizontal, this);

    m_editor = new MDEditor(m_splitter);
    m_previewer = new MDPreviewer(m_splitter);

    m_splitter->addWidget(m_editor);
    m_splitter->addWidget(m_previewer);
    m_splitter->setSizes({600, 600});

    setCentralWidget(m_splitter);
}

void MainWindow::setupMenuBar()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *newAction = fileMenu->addAction(tr("&New"), this, &MainWindow::onNewFile);
    newAction->setShortcut(QKeySequence::New);

    QAction *openAction = fileMenu->addAction(tr("&Open..."), this, &MainWindow::onOpenFile);
    openAction->setShortcut(QKeySequence::Open);

    QAction *saveAction = fileMenu->addAction(tr("&Save"), this, &MainWindow::onSaveFile);
    saveAction->setShortcut(QKeySequence::Save);

    fileMenu->addSeparator();

    QAction *exitAction = fileMenu->addAction(tr("E&xit"), this, &QWidget::close);
    exitAction->setShortcut(QKeySequence::Quit);
}

void MainWindow::setupToolBar()
{
    QToolBar *toolbar = addToolBar(tr("Formatting"));
    toolbar->setMovable(false);
    toolbar->setIconSize(QSize(18, 18));

    toolbar->addAction(tr("↩ Undo"), m_editor, &QPlainTextEdit::undo)->setShortcut(QKeySequence::Undo);
    toolbar->addAction(tr("↪ Redo"), m_editor, &QPlainTextEdit::redo)->setShortcut(QKeySequence::Redo);

    toolbar->addSeparator();

    toolbar->addAction(tr("H1"), [this]() { m_editor->insertAtLineStart("# "); });
    toolbar->addAction(tr("H2"), [this]() { m_editor->insertAtLineStart("## "); });
    toolbar->addAction(tr("H3"), [this]() { m_editor->insertAtLineStart("### "); });

    toolbar->addSeparator();

    toolbar->addAction(tr("B"), [this]() { m_editor->insertMarkdown("**", "**"); });
    toolbar->addAction(tr("I"), [this]() { m_editor->insertMarkdown("*", "*"); });
    toolbar->addAction(tr("S"), [this]() { m_editor->insertMarkdown("~~", "~~"); });
    toolbar->addAction(tr("<>"), [this]() { m_editor->insertMarkdown("`", "`"); });

    toolbar->addSeparator();

    toolbar->addAction(tr("Link"), [this]() { m_editor->insertMarkdown("[", "](url)"); });
    toolbar->addAction(tr("Img"), [this]() { m_editor->insertMarkdown("![", "](image_url)"); });

    toolbar->addAction(tr("UL"), [this]() { m_editor->insertAtLineStart("- "); });
    toolbar->addAction(tr("OL"), [this]() { m_editor->insertAtLineStart("1. "); });

    toolbar->addSeparator();

    toolbar->addAction(tr("\" Quote"), [this]() { m_editor->insertAtLineStart("> "); });
    toolbar->addAction(tr("— HR"), [this]() { m_editor->insertBlock("\n---\n"); });
    toolbar->addAction(tr("Code Block"), [this]() { m_editor->insertMarkdown("```\n", "\n```"); });

    toolbar->setStyleSheet(
        "QToolBar { background: #f5f0e8; border-bottom: 1px solid #ddd; padding: 2px; spacing: 2px; }"
        "QToolButton { background: transparent; border: 1px solid transparent; border-radius: 3px;"
        "  padding: 3px 6px; font-size: 12px; font-weight: bold; color: #555; }"
        "QToolButton:hover { background: #e8e0d0; border: 1px solid #ccc; }"
        "QToolButton:pressed { background: #ddd; }"
    );
}

void MainWindow::onNewFile()
{
    m_editor->clear();
    m_previewer->setHtmlContent(QString());
    m_currentFilePath.clear();
    setWindowTitle(tr("마크다운 에디터"));
}

void MainWindow::onOpenFile()
{
    QString filePath = QFileDialog::getOpenFileName(
        this, tr("Open Markdown File"), QString(),
        tr("Markdown Files (*.md *.markdown);;All Files (*)"));

    if (filePath.isEmpty())
        return;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"),
                             tr("Cannot open file: %1").arg(file.errorString()));
        return;
    }

    m_editor->setPlainText(QString::fromUtf8(file.readAll()));
    m_currentFilePath = filePath;
    setWindowTitle(tr("마크다운 에디터 - %1").arg(filePath));
}

void MainWindow::onSaveFile()
{
    if (m_currentFilePath.isEmpty()) {
        m_currentFilePath = QFileDialog::getSaveFileName(
            this, tr("Save Markdown File"), QString(),
            tr("Markdown Files (*.md *.markdown);;All Files (*)"));
    }

    if (m_currentFilePath.isEmpty())
        return;

    QFile file(m_currentFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"),
                             tr("Cannot save file: %1").arg(file.errorString()));
        return;
    }

    file.write(m_editor->toPlainText().toUtf8());
    setWindowTitle(tr("마크다운 에디터 - %1").arg(m_currentFilePath));
}

void MainWindow::onTextChanged()
{
    QString text = m_editor->toPlainText();
    QString html = m_parser->parse(text);
    m_previewer->setHtmlContent(html);
}
