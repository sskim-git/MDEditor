#include "MDPreviewer.h"

static const char *CSS_STYLE = R"(
<style>
body {
    font-family: 'Segoe UI', sans-serif;
    font-size: 14px;
    line-height: 1.6;
    color: #333;
    padding: 12px;
    max-width: 100%;
}
h1 {
    font-size: 24px;
    border-bottom: 2px solid #eee;
    padding-bottom: 6px;
    color: #111;
}
h2 {
    font-size: 20px;
    border-bottom: 1px solid #eee;
    padding-bottom: 4px;
    color: #222;
}
h3 { font-size: 17px; color: #333; }
h4 { font-size: 15px; color: #444; }
h5 { font-size: 14px; color: #555; }
h6 { font-size: 13px; color: #777; }
code {
    background: #f4f4f4;
    padding: 2px 5px;
    border-radius: 3px;
    font-family: Consolas, monospace;
    font-size: 13px;
    color: #c7254e;
}
pre {
    background: #f8f8f8;
    border: 1px solid #ddd;
    border-radius: 4px;
    padding: 10px;
    overflow-x: auto;
}
pre code {
    background: none;
    padding: 0;
    color: #333;
}
blockquote {
    border-left: 4px solid #4a9eff;
    margin: 8px 0;
    padding: 6px 12px;
    background: #f0f7ff;
    color: #555;
}
a {
    color: #0366d6;
    text-decoration: none;
}
a:hover {
    text-decoration: underline;
}
ul, ol {
    padding-left: 24px;
}
li {
    margin: 3px 0;
}
hr {
    border: none;
    border-top: 1px solid #ddd;
    margin: 16px 0;
}
img {
    max-width: 100%;
}
</style>
)";

MDPreviewer::MDPreviewer(QWidget *parent)
    : QTextBrowser(parent)
{
    setReadOnly(true);
    setOpenExternalLinks(true);
}

void MDPreviewer::setHtmlContent(const QString &html)
{
    QString styled = QString("<html><head>%1</head><body>%2</body></html>")
                         .arg(CSS_STYLE, html);
    setHtml(styled);
}
