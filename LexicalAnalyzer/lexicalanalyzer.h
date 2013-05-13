#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include "highlighter.h"
#include "aboutbox.h"
#include "analyzer.h"
using namespace Ui;

class LexicalAnalyzer : public QMainWindow
{
	Q_OBJECT

private:
	LexicalAnalyzerClass ui;
	Highlighter *highlighter;
	Analyzer *analyzer;
	QFile *file;
	QTextCodec *codec;
	QString path_file, str_src;

	private slots:
		void on_action_new_triggered();
		void on_action_open_triggered();
		void on_action_save_triggered();
		void on_action_quit_triggered();
		void on_action_clear_triggered();
		void on_action_analyse_triggered();
		void on_action_tokenlist_triggered();
		void on_action_about_triggered();
		void on_action_homepage_triggered();

public:
	LexicalAnalyzer(QWidget *parent = 0);
	~LexicalAnalyzer();
	void closeEvent(QCloseEvent *event);
	void initUi();
	bool openfile(QString path_file);
	void showOpenFileDialog();
	bool savefile(QString path_file);
	void newfile();
	bool fileChange();
};

#endif // LEXICALANALYZER_H