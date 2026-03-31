#include "MainWindow.h"
#include "MDEditor.h"
#include "MDPreviewer.h"

#include <QSplitter>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    setupMenuBar();

    setWindowTitle(tr("MDEditor"));
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

void MainWindow::onNewFile()
{
    m_editor->clear();
    m_previewer->setHtmlContent(QString());
    m_currentFilePath.clear();
    setWindowTitle(tr("MDEditor"));
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
    setWindowTitle(tr("MDEditor - %1").arg(filePath));
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
    setWindowTitle(tr("MDEditor - %1").arg(m_currentFilePath));
}
