#ifndef MDPREVIEWER_H
#define MDPREVIEWER_H

#include <QTextBrowser>

class MDPreviewer : public QTextBrowser
{
    Q_OBJECT

public:
    explicit MDPreviewer(QWidget *parent = nullptr);

public slots:
    void setHtmlContent(const QString &html);
};

#endif // MDPREVIEWER_H
