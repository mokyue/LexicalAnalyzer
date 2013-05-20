#ifndef ANALYZER_H
#define ANALYZER_H

#include "ui_lexicalanalyzer.h"
#include <QtCore>
#include <QtGui>

namespace Token
{
	const QString TOKEN_KEY = QStringLiteral("1-100");
	const QString TOKEN_CONSTANT = QStringLiteral("200");
	const QString TOKEN_IDENTIFIER = QStringLiteral("300");
}

class Analyzer
{
private:
	Ui_LexicalAnalyzerClass ui;
	QString str_src;
	QVector<QString> vector_symbols;
	QMap<QString, QString> map_symbolsToken, map_tokenDescription; // 关于Token中文描述的关联容器
	QMap<int, QMap<QString, QVector<QString>>> map_result;
	QMap<int, QMap<QString, QString>> map_error;
	QSettings *slist_token;

public:
	Analyzer(QString str_src, Ui_LexicalAnalyzerClass &ui);
	void initSlist();
	void initSymbolsVector();
	void initSymbolsTokenMap();
	void initTokenDescriptionMap();
	void operate();
	QMap<QString, QVector<QString>> getDivideMap(QString &str_line);
	QMap<QString, QString> getErrorMap(QString &str_line);
	void analyseQuotes(QString &str_line, QMap<QString, QVector<QString>> &map_divide);
	void analyseNumber(QString &str_line, QMap<QString, QVector<QString>> &map_divide);
	void analyseSymbols(QString &str_line, QMap<QString, QVector<QString>> &map_divide);
	void analyseKeys(QString &str_line, QMap<QString, QVector<QString>> &map_divide);
	void analyseIdentifier(QString &str_line, QMap<QString, QVector<QString>> &map_divide);
	void analyseError(QString &str_line, QMap<QString, QString> &map_error_info);
	QList<QString> replaceSpace(QVector<QChar> &vector_line, QList<int> list_match_index);
	bool isIdentifier(QString str_word);
	bool isPrecompileHeader(QString str_line);
	bool isLetter(QChar c);
	bool isDigit(QChar c);
	void showResult();
	void showError();
};

#endif // ANALYZER_H