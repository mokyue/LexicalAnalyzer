#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QtCore>
#include <QtGui>

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE

class Highlighter : public QSyntaxHighlighter
{
	Q_OBJECT

private:
	struct HighlightingRule
	{
		QRegExp pattern;
		QTextCharFormat format;
	};
	QVector<HighlightingRule> highlightingRules;
	QRegExp commentStartExpression;
	QRegExp commentEndExpression;
	QTextCharFormat keywordFormat;
	QTextCharFormat classFormat;
	QTextCharFormat singleLineCommentFormat;
	QTextCharFormat multiLineCommentFormat;
	QTextCharFormat quotationFormat;
	QTextCharFormat functionFormat;

protected:
	void highlightBlock(const QString &text);

public:
	Highlighter(QTextDocument *parent = 0);
};

#endif