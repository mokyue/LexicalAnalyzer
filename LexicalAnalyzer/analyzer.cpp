#include "analyzer.h"

Analyzer::Analyzer(QString str_src, Ui_LexicalAnalyzerClass &ui)
{
	this->str_src = str_src;
	this->ui = ui;
	initSlist();
	initSymbolsVector();
	initTokenDescriptionMap();
	operate();
}

void Analyzer::initSlist()
{
	slist_token = new QSettings(":/ini/tokenlist", QSettings::IniFormat, 0);
	slist_token->setIniCodec(QTextCodec::codecForName("GB2312"));
}

void Analyzer::initSymbolsVector()
{
	vector_symbols << "+" << "-" << "*" << "/" << "%" << "=" << "<" << ">" << "!"
		<< "&" << "" << "" << "" << "" << "" << "" << "" << "" << "" << "";
}

void Analyzer::initTokenDescriptionMap() // 初始化map_tokenDescription
{
	map_tokenDescription[Token::TOKEN_CONSTANT] = QStringLiteral("常数");
	map_tokenDescription[Token::TOKEN_IDENTIFIER] = QStringLiteral("标识符");
}

void Analyzer::operate()
{
	QMap<int, QString> map_line;
	QString str_tmp;
	int num_line = 0;
	str_src.append("\n"); // 代码分析结尾符号
	for each (QChar var in str_src)
	{
		if (var != '\n')
		{
			str_tmp.append(var);
		}
		else
		{
			num_line++;
			map_line[num_line] = str_tmp;
			str_tmp.clear();
		}
	}
	QMapIterator<int, QString> iter_map_line(map_line);
	while (iter_map_line.hasNext())
	{
		iter_map_line.next();
		QString str_line = iter_map_line.value();
		map_result[iter_map_line.key()] = getDivideMap(str_line);
		// qDebug() << str_line;
	}
	qDebug() << map_result;
}

QMap<QString, QVector<QString>> Analyzer::getDivideMap(QString &str_line)
{
	QMap<QString, QVector<QString>> map_divide;
	analyseQuotes(str_line, map_divide);
	analyseNumber(str_line, map_divide);
	analyseSymbols(str_line, map_divide);
	qDebug() << str_line;
	return map_divide;
}

void Analyzer::analyseQuotes(QString &str_line, QMap<QString, QVector<QString>> &map_divide)
{
	QVector<QString> vector_info;
	QVector<QChar> vector_line;
	for each (QChar var in str_line)
	{
		vector_line.push_back(var);
	}

	QList<int> list_match_index_d, list_match_index_s;
	for(int i = 0; i < str_line.length(); i++)
	{
		if (str_line.at(i) == '\"')
		{
			list_match_index_d.push_back(i);
		}
		if (str_line.at(i) == '\'')
		{
			list_match_index_s.push_back(i);
		}
	}
	QList<QString> list_quotes_txt_d = replaceSpace(vector_line, list_match_index_d); // 引号内容替换为空格
	QListIterator<QString> iter_list_quotes_txt_d(list_quotes_txt_d);
	QString quotes_txt_d;
	while (iter_list_quotes_txt_d.hasNext())
	{
		quotes_txt_d = iter_list_quotes_txt_d.next();
		if (quotes_txt_d != "")
		{
			vector_info.clear();
			QString str_token = Token::TOKEN_CONSTANT;
			vector_info.push_back(str_token);
			vector_info.push_back(map_tokenDescription[str_token]);
			map_divide[quotes_txt_d] = vector_info;
		}
	}
	QList<QString> list_quotes_txt_s = replaceSpace(vector_line, list_match_index_s);
	QListIterator<QString> iter_list_quotes_txt_s(list_quotes_txt_s);
	QString str_quoteText;
	while (iter_list_quotes_txt_s.hasNext())
	{
		str_quoteText = iter_list_quotes_txt_s.next();
		if (str_quoteText != "")
		{
			vector_info.clear();
			QString str_token = Token::TOKEN_CONSTANT;
			vector_info.push_back(str_token);
			vector_info.push_back(map_tokenDescription[str_token]);
			map_divide[str_quoteText] = vector_info;
		}
	}
	str_line.clear();
	for each (QChar var in vector_line)
	{
		str_line.append(var);
	}
}

QList<QString> Analyzer::replaceSpace(QVector<QChar> &vector_line, QList<int> list_match_index)
{
	QList<QString> list_quotes_txt;
	QString quotes_txt;
	QListIterator<int> iter_list_match_index(list_match_index);
	int match_iter_index = 0, begin_index = 0, end_index = 0;
	bool flag = false;
	while (iter_list_match_index.hasNext())
	{
		match_iter_index++;
		if (match_iter_index % 2 != 0) // 奇数
		{
			begin_index = iter_list_match_index.next();
		}
		else
		{
			end_index = iter_list_match_index.next();
			flag = true;
		}
		if (flag)
		{
			quotes_txt.clear();
			for (int i = begin_index + 1; i < end_index; i++)
			{
				quotes_txt.append(vector_line[i]);
				vector_line[i] = ' ';
			}
			list_quotes_txt.push_back(quotes_txt);
			flag = !flag;
		}
	}
	return list_quotes_txt;
}

void Analyzer::analyseNumber(QString &str_line, QMap<QString, QVector<QString>> &map_divide)
{
	QVector<QString> vector_info;
	QVector<QChar> vector_line;
	QString str_number;
	for each (QChar var in str_line)
	{
		vector_line.push_back(var);
	}
	bool flag = false;
	for (int i = 0; i < str_line.length(); i++)
	{
		QChar c = str_line.at(i);
		if (isDigit(c))
		{
			if (i != 0)
			{
				if (!isLetter(str_line.at(i - 1))) // 如果前一个不是字母
				{
					str_number.append(c);
					vector_line[i] = ' ';
					flag = true;
				}
			}
			else
			{
				str_number.append(c);
				vector_line[i] = ' ';
				flag = true;
			}
		}
		else
		{
			if (c == '.' && flag)
			{
				str_number.append(c);
				vector_line[i] = ' ';
			} 
			else if (flag)
			{
				vector_info.clear();
				QString str_token = Token::TOKEN_CONSTANT;
				vector_info.push_back(str_token);
				vector_info.push_back(map_tokenDescription[str_token]);
				map_divide[str_number] = vector_info;
				str_number.clear();
				flag = !flag;
			}
		}
	}
	str_line.clear();
	for each (QChar var in vector_line)
	{
		str_line.append(var);
	}
}

void Analyzer::analyseSymbols(QString &str_line, QMap<QString, QVector<QString>> &map_divide)
{

}

bool Analyzer::isLetter(QChar c)
{
	if(((c <= 'z') && (c >= 'a')) || ((c <= 'Z') && (c >= 'A')))
		return true;
	else
		return false;
}

bool Analyzer::isDigit(QChar c)
{
	if(c >= '0' && c <= '9')
		return true;
	else
		return false;
}

void Analyzer::showResult()
{
	int count_result = map_result.count();
	QStandardItemModel *itemModel_token = qobject_cast<QStandardItemModel *>(ui.tableView_token->model());
	QMapIterator<int, QMap<QString, QVector<QString>>> iter_result(map_result);
	int number_row = 0;
	while (iter_result.hasNext())
	{
		iter_result.next();
		int number_line = iter_result.key();
		QMap<QString, QVector<QString>> map_divide = iter_result.value();
		QMapIterator<QString, QVector<QString>> iter_map_divide(map_divide);
		while (iter_map_divide.hasNext())
		{
			iter_map_divide.next();
			itemModel_token->setItem(number_row, 0, new QStandardItem(QString::number(number_line)));
			itemModel_token->setItem(number_row, 1, new QStandardItem(iter_map_divide.key()));
			itemModel_token->setItem(number_row, 2, new QStandardItem(iter_map_divide.value().at(0)));
			itemModel_token->setItem(number_row, 3, new QStandardItem(iter_map_divide.value().at(1)));
			number_row++;
		}
	}
	for (int row = 0; row < number_row; row++)
	{
		for (int colum = 0; colum < 4; colum++)
		{
			itemModel_token->item(row, colum)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		}
	}
}