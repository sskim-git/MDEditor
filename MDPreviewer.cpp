#include "MDPreviewer.h"

MDPreviewer::MDPreviewer(QWidget *parent)
    : QTextBrowser(parent)
{
    setReadOnly(true);
    setOpenExternalLinks(true);

    QFont font("Segoe UI", 11);
    setFont(font);
}

void MDPreviewer::setHtmlContent(const QString &html)
{
    setHtml(html);
}
