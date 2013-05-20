#include "lexicalanalyzer.h"

LexicalAnalyzer::LexicalAnalyzer(QWidget *parent)
	: QMainWindow(parent)
{
	initUi();
}

LexicalAnalyzer::~LexicalAnalyzer()
{
	// ���������ͷ��ڴ�
}

void LexicalAnalyzer::closeEvent(QCloseEvent *event)
{
	if (fileChange())
	{
		QMessageBox *messageBox = new QMessageBox(this);
		messageBox->setWindowTitle(QStringLiteral("ϵͳ��ʾ"));
		QPixmap pixmap_logo(":/img/logo_s");
		messageBox->setIconPixmap(pixmap_logo);
		messageBox->setText(QStringLiteral("Դ���Ѿ��Ķ����Ƿ񱣴棿"));
		QPushButton *button_save = messageBox->addButton(QStringLiteral("����"), QMessageBox::ActionRole);
		QPushButton *button_discard  = messageBox->addButton(QStringLiteral("������"), QMessageBox::ActionRole);
		QPushButton *button_cancel = messageBox->addButton(QStringLiteral("ȡ��"), QMessageBox::ActionRole);
		messageBox->exec();
		if (messageBox->clickedButton() == button_save)
		{
			on_action_save_triggered();
			event->accept();
		} 
		else if (messageBox->clickedButton() == button_discard)
		{
			event->accept();
		}
		else if (messageBox->clickedButton() == button_cancel)
		{
			event->ignore();
		}
	} 
	else
	{
		QMessageBox *messageBox = new QMessageBox(this);
		messageBox->setWindowTitle(QStringLiteral("ϵͳ��ʾ"));
		QPixmap *pixmap_logo = new QPixmap(":/img/logo_s");
		messageBox->setIconPixmap(*pixmap_logo);
		messageBox->setText(QStringLiteral("ȷ��Ҫ�˳���"));
		QPushButton *button_ok = messageBox->addButton(QStringLiteral("ȷ��"), QMessageBox::ActionRole);
		messageBox->addButton(QStringLiteral("ȡ��"), QMessageBox::ActionRole);
		messageBox->exec();
		if (messageBox->clickedButton() == button_ok)
		{
			event->accept();
		} 
		else
		{
			event->ignore();
		}
	}
}

void LexicalAnalyzer::initUi()
{
	ui.setupUi(this);
	path_file = "";
	codec = QTextCodec::codecForName("System");
	QFont font;
	font.setFamily("Source Code Pro Semibold");
	font.setFixedPitch(true);
	font.setPointSize(10);
	ui.textEdit_code->setFont(font);
	ui.textEdit_code->setText(QStringLiteral("<font face=\"΢���ź�\" size=13><center>[ �½�Դ���뿪ʼ���� ]</center></font>"));
	str_src = ui.textEdit_code->toPlainText();
	highlighter = new Highlighter(ui.textEdit_code->document());
	ui.textEdit_code->setEnabled(false);
	ui.action_clear->setEnabled(false);
	ui.action_save->setEnabled(false);
	ui.action_analyse->setEnabled(false);

	QStandardItemModel *itemModel_token = new QStandardItemModel();
	itemModel_token->setHorizontalHeaderItem(0, new QStandardItem(QStringLiteral("�к�")));
	itemModel_token->setHorizontalHeaderItem(1, new QStandardItem(QStringLiteral("����")));
	itemModel_token->setHorizontalHeaderItem(2, new QStandardItem(QStringLiteral("Token")));
	itemModel_token->setHorizontalHeaderItem(3, new QStandardItem(QStringLiteral("����")));
	ui.tableView_token->setModel(itemModel_token);
	ui.tableView_token->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableView_token->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.tableView_token->setColumnWidth(0, 60);
	ui.tableView_token->setColumnWidth(2, 68);
	ui.tableView_token->setColumnWidth(3, 162);

	QStandardItemModel *itemModel_error = new QStandardItemModel();
	itemModel_error->setHorizontalHeaderItem(0, new QStandardItem(QStringLiteral("�����к�")));
	itemModel_error->setHorizontalHeaderItem(1, new QStandardItem(QStringLiteral("����")));
	itemModel_error->setHorizontalHeaderItem(2, new QStandardItem(QStringLiteral("������Ϣ")));
	ui.tableView_error->setModel(itemModel_error);
	ui.tableView_error->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableView_error->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.tableView_error->setColumnWidth(0, 70);
	ui.tableView_error->setColumnWidth(1, 320);

	QFont font_toolbar;
	font_toolbar.setFamily(QStringLiteral("΢���ź�"));
	ui.toolBar->setFont(font_toolbar);
	ui.toolBar->addAction(ui.action_new);
	ui.toolBar->addAction(ui.action_open);
	ui.toolBar->addAction(ui.action_save);
	ui.toolBar->addSeparator();
	ui.toolBar->addAction(ui.action_clear);
	ui.toolBar->addAction(ui.action_analyse);
	ui.toolBar->addSeparator();
	ui.toolBar->addAction(ui.action_tokenlist);
	ui.toolBar->addAction(ui.action_about);
	ui.toolBar->addAction(ui.action_homepage);

	QLabel *label_statusPic = new QLabel(this);
	label_statusPic->setPixmap(QPixmap(":/img/logo_ss"));
	ui.statusBar->addWidget(label_statusPic);
	label_statusText = new QLabel(this);
	label_statusText->setText(QStringLiteral("����"));
	ui.statusBar->addWidget(label_statusText);

	timer_status = new QTimer(this);
	connect(timer_status, SIGNAL(timeout()), this, SLOT(on_timer_status_timeout()));
}

bool LexicalAnalyzer::openfile(QString path)
{
	path_file = path;
	file = new QFile(path_file);
	if (file->open(QIODevice::ReadOnly | QIODevice::Text))
	{
		str_src = codec->toUnicode(file->readAll());
		ui.textEdit_code->setPlainText(str_src);
		setWindowTitle(QStringLiteral("Lexizer �ʷ������� - ") + file->fileName());
		file->close();
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::savefile(QString path_file)
{
	file = new QFile(path_file);
	if (file->open(QIODevice::Text | QIODevice::WriteOnly))
	{
		QTextStream out(file);
		str_src = ui.textEdit_code->toPlainText();
		out << str_src;
		setWindowTitle(QStringLiteral("Lexizer �ʷ������� - ") + path_file);
		file->close();
		showState(ui.action_save->text());
	}
	return true;
}

void LexicalAnalyzer::newfile()
{
	qDebug() << "NEW";
	path_file = "";
	ui.textEdit_code->clear();
	ui.action_save->setEnabled(true);
	ui.action_analyse->setEnabled(true);
	ui.textEdit_code->setEnabled(true);
	ui.action_clear->setEnabled(true);
	setWindowTitle(QStringLiteral("Lexizer �ʷ������� - δ����.cpp"));
}

bool LexicalAnalyzer::fileChange()
{
	QString str_tmp = ui.textEdit_code->toPlainText();
	if (str_tmp != str_src && str_tmp != "")
		return true;
	else
		return false;
}

void LexicalAnalyzer::on_action_new_triggered()
{
	if (fileChange())
	{
		QMessageBox *messageBox = new QMessageBox(this);
		messageBox->setWindowTitle(QStringLiteral("ϵͳ��ʾ"));
		messageBox->setText(QStringLiteral("Դ���Ѿ��Ķ����Ƿ񱣴棿"));
		QPushButton *button_save = messageBox->addButton(QStringLiteral("����"), QMessageBox::ActionRole);
		QPushButton *button_discard  = messageBox->addButton(QStringLiteral("������"), QMessageBox::ActionRole);
		messageBox->addButton(QStringLiteral("ȡ��"), QMessageBox::ActionRole);
		messageBox->exec();
		if (messageBox->clickedButton() == button_save)
		{
			on_action_save_triggered();
			newfile();
			showState(ui.action_new->text());
		} 
		else if (messageBox->clickedButton() == button_discard)
		{
			newfile();
			showState(ui.action_new->text());
		}
	} 
	else
	{
		newfile();
		showState(ui.action_new->text());
	}
}

void LexicalAnalyzer::on_action_open_triggered()
{
	if (fileChange())
	{
		QMessageBox *messageBox = new QMessageBox(this);
		messageBox->setWindowTitle(QStringLiteral("ϵͳ��ʾ"));
		messageBox->setText(QStringLiteral("Դ���Ѿ��Ķ����Ƿ񱣴棿"));
		QPushButton *button_save = messageBox->addButton(QStringLiteral("����"), QMessageBox::ActionRole);
		QPushButton *button_discard  = messageBox->addButton(QStringLiteral("������"), QMessageBox::ActionRole);
		messageBox->addButton(QStringLiteral("ȡ��"), QMessageBox::ActionRole);
		messageBox->exec();
		if (messageBox->clickedButton() == button_save)
		{
			on_action_save_triggered();
			showOpenFileDialog();
		} 
		else if (messageBox->clickedButton() == button_discard)
		{
			showOpenFileDialog();
		}
	} 
	else
	{
		showOpenFileDialog();
	}
}

void LexicalAnalyzer::showOpenFileDialog()
{
	path_file = QFileDialog::getOpenFileName(this, QStringLiteral("��Դ����"), path_file, QStringLiteral("Դ���ĵ� (*.cpp *.c *.h);;�ı��ĵ� (*.txt);;�����ļ� (*.*)"));
	if (!path_file.isNull())
	{
		if (!openfile(path_file))
		{
			qDebug() << "OPEN FAILD";
			QMessageBox *messageBox = new QMessageBox(this);
			messageBox->setWindowTitle(QStringLiteral("ϵͳ��ʾ"));
			messageBox->setText(QStringLiteral("Դ���ʧ�ܣ�"));
			messageBox->addButton(QStringLiteral("ȷ��"), QMessageBox::ActionRole);
			messageBox->exec();
		}
		else
		{
			ui.action_save->setEnabled(true);
			ui.action_analyse->setEnabled(true);
			ui.textEdit_code->setEnabled(true);
			ui.action_clear->setEnabled(true);
			showState(ui.action_open->text());
			qDebug() << "OPEN";
		}
	} 
	else
	{
		qDebug() << "CANCEL OPEN";
	}
}

void LexicalAnalyzer::on_action_save_triggered()
{
	path_file = QFileDialog::getSaveFileName(this, QStringLiteral("����Դ����"), path_file, QStringLiteral("Դ���ĵ� (*.cpp *.c *.h);;�ı��ĵ� (*.txt);;�����ļ� (*.*)"));
	if (!path_file.isNull())
	{
		if (!savefile(path_file))
		{
			qDebug() << "SAVE FAILD";
			QMessageBox *messageBox = new QMessageBox(this);
			messageBox->setWindowTitle(QStringLiteral("ϵͳ��ʾ"));
			messageBox->setText(QStringLiteral("Դ�뱣��ʧ�ܣ�"));
			messageBox->addButton(QStringLiteral("ȷ��"), QMessageBox::ActionRole);
			messageBox->exec();
		}
	} 
	else
	{
		qDebug() << "CANCEL SAVE";
	}
}

void LexicalAnalyzer::on_action_quit_triggered()
{
	close();
}

void LexicalAnalyzer::on_action_clear_triggered()
{
	ui.textEdit_code->clear();
	clearResult();
	showState(ui.action_clear->text());
}

void LexicalAnalyzer::clearResult()
{
	QStandardItemModel *itemModel_token = qobject_cast<QStandardItemModel *>(ui.tableView_token->model());
	itemModel_token->removeRows(0, itemModel_token->rowCount());
	QStandardItemModel *itemModel_error = qobject_cast<QStandardItemModel *>(ui.tableView_error->model());
	itemModel_error->removeRows(0, itemModel_error->rowCount());
}

void LexicalAnalyzer::on_action_analyse_triggered()
{
	qDebug() << "ANALYSE";
	clearResult();
	str_src = ui.textEdit_code->toPlainText();
	analyzer = new Analyzer(str_src, ui);
	analyzer->showResult();
	analyzer->showError();
	delete analyzer;
	showState(QStringLiteral("��������"));
}

void LexicalAnalyzer::on_action_tokenlist_triggered()
{
	qDebug() << "SHOW TOKEN LIST";
	showState(QStringLiteral("��Token�б�"));
}

void LexicalAnalyzer::on_action_about_triggered()
{
	qDebug() << "ABOUT";
	AboutBox *aboutbox = new AboutBox(this);
	showState(QStringLiteral("�鿴������Ϣ"));
	aboutbox->show();
}

void LexicalAnalyzer::on_action_homepage_triggered()
{
	qDebug() << "HOMEPAGE";
	const QUrl url("http://github.com/mokyue");
	QDesktopServices::openUrl(url);
	showState(QStringLiteral("���ʿ�������ҳ"));
}

void LexicalAnalyzer::showState(QString str_state)
{
	label_statusText->setText(str_state);
	timer_status->start(5000);
}

void LexicalAnalyzer::on_timer_status_timeout()
{
	label_statusText->setText(QStringLiteral("����"));
	timer_status->stop();
}