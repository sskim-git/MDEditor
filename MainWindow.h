#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MDEditor;
class MDPreviewer;
class QSplitter;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

private slots:
    void onNewFile();
    void onOpenFile();
    void onSaveFile();

private:
    void setupUI();
    void setupMenuBar();

    QSplitter *m_splitter;
    MDEditor *m_editor;
    MDPreviewer *m_previewer;
    QString m_currentFilePath;
};

#endif // MAINWINDOW_H
