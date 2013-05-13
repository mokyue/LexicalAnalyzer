#include "lexicalanalyzer.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	app.setStyle("fusion");
	LexicalAnalyzer analyzer;
	analyzer.show();
	return app.exec();
}