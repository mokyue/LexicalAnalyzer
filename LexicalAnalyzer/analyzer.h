#ifndef ANALYZER_H
#define ANALYZER_H

#include "ui_lexicalanalyzer.h"
#include <QtCore>
#include <QtGui>

namespace Token
{
	const QString TOKEN_CONSTANT = QStringLiteral("200");
	const QString TOKEN_IDENTIFIER = QStringLiteral("300");
}

class Analyzer
{
private:
	Ui_LexicalAnalyzerClass ui;
	QString str_src;
	QVector<QString> vector_symbols;
	QMap<QString, QString> map_tokenDescription; // 关于Token中文描述的关联容器
	QMap<int, QMap<QString, QVector<QString>>> map_result;
	QSettings *slist_token;

public:
	Analyzer(QString str_src, Ui_LexicalAnalyzerClass &ui);
	void initSlist();
	void initSymbolsVector();
	void initTokenDescriptionMap();
	void operate();
	QMap<QString, QVector<QString>> getDivideMap(QString &str_line);
	void analyseQuotes(QString &str_line, QMap<QString, QVector<QString>> &map_divide);
	void analyseNumber(QString &str_line, QMap<QString, QVector<QString>> &map_divide);
	void analyseSymbols(QString &str_line, QMap<QString, QVector<QString>> &map_divide);
	QList<QString> replaceSpace(QVector<QChar> &vector_line, QList<int> list_match_index);
	bool isLetter(QChar c);
	bool isDigit(QChar c);
	void showResult();
};

#endif // ANALYZER_H