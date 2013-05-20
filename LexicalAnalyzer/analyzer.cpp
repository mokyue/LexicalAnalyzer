#include "analyzer.h"

Analyzer::Analyzer(QString str_src, Ui_LexicalAnalyzerClass &ui)
{
	this->str_src = str_src;
	this->ui = ui;
	initSlist();
	initSymbolsVector();
	initSymbolsTokenMap();
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
	vector_symbols << "+" << "-" << "*" << "/" << "%" << "=" << "<" << ">"
		<< "!" << "&" << "." << "~" << "^" << "|" << ":" << "?" << "[" << "]"
		<< "(" << ")" << "{" << "}" << ";" << "," << "#" << "\\" << "::" << "+="
		<< "-=" << "*=" << "/=" << "%=" << "++" << "--" << "==" << "<=" << ">="
		<< "!=" << "&&" << "||" << "<<" << ">>" << "->" << "&=" << "^=" << "|="
		<< ">>=" << "<<=" << "/*" << "*/";
	// qDebug() << vector_symbols.size();
}

void Analyzer::initSymbolsTokenMap()
{
	map_symbolsToken["+"] = "c100";
	map_symbolsToken["-"] = "c101";
	map_symbolsToken["*"] = "c102";
	map_symbolsToken["/"] = "c103";
	map_symbolsToken["%"] = "c104";
	map_symbolsToken["="] = "c105";
	map_symbolsToken["<"] = "c106";
	map_symbolsToken[">"] = "c107";
	map_symbolsToken["!"] = "c108";
	map_symbolsToken["&"] = "c109";
	map_symbolsToken["."] = "c110";
	map_symbolsToken["~"] = "c111";
	map_symbolsToken["^"] = "c112";
	map_symbolsToken["|"] = "c113";
	map_symbolsToken[":"] = "c114";
	map_symbolsToken["?"] = "c115";
	map_symbolsToken["::"] = "c116";
	map_symbolsToken["+="] = "c117";
	map_symbolsToken["-="] = "c118";
	map_symbolsToken["*="] = "c119";
	map_symbolsToken["/="] = "c120";
	map_symbolsToken["%="] = "c121";
	map_symbolsToken["++"] = "c122";
	map_symbolsToken["--"] = "c123";
	map_symbolsToken["=="] = "c124";
	map_symbolsToken["<="] = "c125";
	map_symbolsToken[">="] = "c126";
	map_symbolsToken["!="] = "c127";
	map_symbolsToken["&&"] = "c128";
	map_symbolsToken["||"] = "c129";
	map_symbolsToken["<<"] = "c130";
	map_symbolsToken[">>"] = "c131";
	map_symbolsToken["->"] = "c132";
	map_symbolsToken["&="] = "c133";
	map_symbolsToken["^="] = "c134";
	map_symbolsToken["|="] = "c135";
	map_symbolsToken[">>="] = "c136";
	map_symbolsToken["<<="] = "c137";
	map_symbolsToken["["] = "e301";
	map_symbolsToken["]"] = "e302";
	map_symbolsToken["("] = "e303";
	map_symbolsToken[")"] = "e304";
	map_symbolsToken["{"] = "e305";
	map_symbolsToken["}"] = "e306";
	map_symbolsToken[";"] = "e307";
	map_symbolsToken[","] = "e308";
	map_symbolsToken["#"] = "e309";
	map_symbolsToken["\\"] = "e310";
	map_symbolsToken["/*"] = "e311";
	map_symbolsToken["*/"] = "e312";
	map_symbolsToken["\""] = "e313";
	map_symbolsToken["\'"] = "e314";
}

void Analyzer::initTokenDescriptionMap() // 初始化map_tokenDescription
{
	map_tokenDescription[Token::TOKEN_CONSTANT] = QStringLiteral("常数");
	map_tokenDescription[Token::TOKEN_IDENTIFIER] = QStringLiteral("标识符");
	map_tokenDescription[Token::TOKEN_KEY] = QStringLiteral("关键词");
	map_tokenDescription[map_symbolsToken["["].mid(1)] = QStringLiteral("界符（左中括号）");
	map_tokenDescription[map_symbolsToken["]"].mid(1)] = QStringLiteral("界符（右中括号）");
	map_tokenDescription[map_symbolsToken["("].mid(1)] = QStringLiteral("界符（左小括号）");
	map_tokenDescription[map_symbolsToken[")"].mid(1)] = QStringLiteral("界符（右小括号）");
	map_tokenDescription[map_symbolsToken["{"].mid(1)] = QStringLiteral("界符（左大括号）");
	map_tokenDescription[map_symbolsToken["}"].mid(1)] = QStringLiteral("界符（右大括号）");
	map_tokenDescription[map_symbolsToken[";"].mid(1)] = QStringLiteral("界符");
	map_tokenDescription[map_symbolsToken[","].mid(1)] = QStringLiteral("界符");
	map_tokenDescription[map_symbolsToken["#"].mid(1)] = QStringLiteral("界符");
	map_tokenDescription[map_symbolsToken["\\"].mid(1)] = QStringLiteral("界符");
	map_tokenDescription[map_symbolsToken["/*"].mid(1)] = QStringLiteral("界符（注释块开始符）");
	map_tokenDescription[map_symbolsToken["*/"].mid(1)] = QStringLiteral("界符（注释块结束符）");
	map_tokenDescription[map_symbolsToken["\""].mid(1)] = QStringLiteral("双引号");
	map_tokenDescription[map_symbolsToken["\'"].mid(1)] = QStringLiteral("单引号");
	map_tokenDescription["<"] = QStringLiteral("左尖括号");
	map_tokenDescription[">"] = QStringLiteral("右尖括号");
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
		map_error[iter_map_line.key()] = getErrorMap(str_line);
		// qDebug() << str_line;
	}
	// qDebug() << map_result;
}

QMap<QString, QVector<QString>> Analyzer::getDivideMap(QString &str_line)
{
	QMap<QString, QVector<QString>> map_divide;
	str_line.append(" "); // 行代码分析结尾符号
	analyseQuotes(str_line, map_divide);
	analyseNumber(str_line, map_divide);
	analyseSymbols(str_line, map_divide);
	analyseKeys(str_line, map_divide);
	analyseIdentifier(str_line, map_divide);
	//qDebug() << str_line;
	return map_divide;
}

QMap<QString, QString> Analyzer::getErrorMap(QString &str_line)
{
	QMap<QString, QString> map_error_info;
	analyseError(str_line, map_error_info);
	return map_error_info;
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
		if (isPrecompileHeader(str_line) && (str_line.at(i) == '<' || str_line.at(i) == '>'))
		{
			list_match_index_d.push_back(i);
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
	QVector<QChar> vector_tmp;
	QVector<QString> vector_info;
	for each (QChar var in str_line)
	{
		vector_tmp.push_back(var);
	}
	bool flag = false;
	QString str_symbol;
	for (int i = 0; i < str_line.length(); i++)
	{
		QChar c = str_line.at(i);
		if (flag)
		{
			str_symbol.append(c);
			if (!vector_symbols.contains(str_symbol))
			{
				vector_info.clear();
				str_symbol = str_symbol.mid(0, str_symbol.length() - 1);
				QString str_tokenInfo = map_symbolsToken[str_symbol];
				QString str_token = str_tokenInfo.mid(1);
				vector_info.push_back(str_token);
				if (str_tokenInfo.at(0) == 'e') // 界符
				{
					vector_info.push_back(map_tokenDescription[str_token]);
				}
				else if ((str_symbol == "<" || str_symbol == ">") && isPrecompileHeader(str_line))
				{
					vector_info.push_back(map_tokenDescription[str_symbol]);
				}
				else // 运算符
				{
					vector_info.push_back(QStringLiteral("运算符"));
				}
				map_divide[str_symbol] = vector_info;
				str_symbol.clear();
				flag = false;
			}
			else
			{
				vector_tmp[i] = ' ';
			}
		}
		if (vector_symbols.contains(c) && !flag)
		{
			str_symbol.append(c);
			vector_tmp[i] = ' ';
			flag = true;
		}
	}
	str_line.clear();
	for each (QChar var in vector_tmp)
	{
		str_line.append(var);
	}
}

void Analyzer::analyseKeys(QString &str_line, QMap<QString, QVector<QString>> &map_divide)
{
	QVector<QString> vector_word, vector_info;
	QString str_tmp;
	for (int i = 0; i < str_line.length(); i++)
	{
		if (str_line.at(i) != ' ')
		{
			str_tmp.append(str_line.at(i));
		} 
		else
		{
			QString token_key = slist_token->value("TOKEN/" + str_tmp).toString();
			if (token_key != "")
			{
				vector_info.clear();
				QString str_token = token_key.mid(1);
				vector_info.push_back(str_token);
				vector_info.push_back(map_tokenDescription[Token::TOKEN_KEY]);
				map_divide[str_tmp] = vector_info;
			}
			else if (str_tmp.trimmed() != "")
				vector_word.push_back(str_tmp);
			str_tmp.clear();
		}
	}
	str_line.clear();
	for each (QString var in vector_word)
	{
		str_line.append(var + " ");
	}
}

void Analyzer::analyseIdentifier(QString &str_line, QMap<QString, QVector<QString>> &map_divide)
{
	QString str_tmp;
	QVector<QString> vector_word, vector_info;
	for (int i = 0; i < str_line.length(); i++)
	{
		if (str_line.at(i) != ' ')
		{
			str_tmp.append(str_line.at(i));
		} 
		else
		{
			if (isIdentifier(str_tmp))
			{
				vector_info.clear();
				QString str_token = Token::TOKEN_IDENTIFIER;
				vector_info.push_back(str_token);
				vector_info.push_back(map_tokenDescription[str_token]);
				map_divide[str_tmp] = vector_info;
			}
			else if (str_tmp.trimmed() != "")
				vector_word.push_back(str_tmp);
			str_tmp.clear();
		}
	}
	str_line.clear();
	for each (QString var in vector_word)
	{
		str_line.append(var + " ");
	}
}

void Analyzer::analyseError(QString &str_line, QMap<QString, QString> &map_error_info)
{
	qDebug() << str_line;
	QString str_tmp;
	for (int i = 0; i < str_line.length(); i++)
	{
		if (str_line.at(i) != ' ')
		{
			str_tmp.append(str_line.at(i));
		} 
		else
		{
			map_error_info[str_tmp] = QStringLiteral("无法识别单词");
			str_tmp.clear();
		}
	}
}

bool Analyzer::isIdentifier(QString str_word)
{
	if (isDigit(str_word.at(0))) // 首字母不是数字
		return false;
	for(int i = 0; i < str_word.length(); i++)
	{
		QChar c = str_word.at(i);
		if (isLetter(c) || isDigit(c) || c == '_') {}
		else
			return false;
	}
	return true;
}

bool Analyzer::isPrecompileHeader(QString str_line)
{
	for (int i = 0; i < str_line.length(); i++)
	{
		if (str_line.at(i) == 'i') // 'i' for "include"
		{
			if (str_line.mid(i, 7) == "include")
				return true;
		}
	}
	return false;
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

void Analyzer::showError()
{
	QStandardItemModel *itemModel_error = qobject_cast<QStandardItemModel *>(ui.tableView_error->model());
	QMapIterator<int, QMap<QString, QString>> iter_error(map_error);
	int number_row = 0;
	while (iter_error.hasNext())
	{
		iter_error.next();
		int number_line = iter_error.key();
		QMap<QString, QString> map_divide = iter_error.value();
		QMapIterator<QString, QString> iter_map_divide(map_divide);
		while (iter_map_divide.hasNext())
		{
			iter_map_divide.next();
			itemModel_error->setItem(number_row, 0, new QStandardItem(QString::number(number_line)));
			itemModel_error->setItem(number_row, 1, new QStandardItem(iter_map_divide.key()));
			itemModel_error->setItem(number_row, 2, new QStandardItem(iter_map_divide.value()));
			number_row++;
		}
	}
	for (int row = 0; row < number_row; row++)
	{
		for (int colum = 0; colum < 3; colum++)
		{
			itemModel_error->item(row, colum)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		}
	}
}