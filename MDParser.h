#ifndef MDPARSER_H
#define MDPARSER_H

#include <QObject>
#include <QList>

class IMarkdownRule;

class MDParser : public QObject
{
    Q_OBJECT

public:
    explicit MDParser(QObject *parent = nullptr);
    ~MDParser() override;

    QString parse(const QString &text) const;

private:
    QList<IMarkdownRule*> m_rules;
};

#endif // MDPARSER_H
