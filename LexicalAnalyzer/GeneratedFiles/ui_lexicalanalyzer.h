/********************************************************************************
** Form generated from reading UI file 'lexicalanalyzer.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEXICALANALYZER_H
#define UI_LEXICALANALYZER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LexicalAnalyzerClass
{
public:
    QAction *action_open;
    QAction *action_quit;
    QAction *action_new;
    QAction *action_tokenlist;
    QAction *action_about;
    QAction *action_homepage;
    QAction *action_save;
    QAction *action_clear;
    QAction *action_analyse;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter_horizontal;
    QTextEdit *textEdit_code;
    QSplitter *splitter_vertical;
    QTableView *tableView_token;
    QTableView *tableView_error;
    QMenuBar *menuBar;
    QMenu *menu_file;
    QMenu *menu_help;
    QMenu *menu_operate;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *LexicalAnalyzerClass)
    {
        if (LexicalAnalyzerClass->objectName().isEmpty())
            LexicalAnalyzerClass->setObjectName(QStringLiteral("LexicalAnalyzerClass"));
        LexicalAnalyzerClass->resize(1000, 557);
        action_open = new QAction(LexicalAnalyzerClass);
        action_open->setObjectName(QStringLiteral("action_open"));
        action_quit = new QAction(LexicalAnalyzerClass);
        action_quit->setObjectName(QStringLiteral("action_quit"));
        action_new = new QAction(LexicalAnalyzerClass);
        action_new->setObjectName(QStringLiteral("action_new"));
        action_tokenlist = new QAction(LexicalAnalyzerClass);
        action_tokenlist->setObjectName(QStringLiteral("action_tokenlist"));
        action_about = new QAction(LexicalAnalyzerClass);
        action_about->setObjectName(QStringLiteral("action_about"));
        action_homepage = new QAction(LexicalAnalyzerClass);
        action_homepage->setObjectName(QStringLiteral("action_homepage"));
        action_save = new QAction(LexicalAnalyzerClass);
        action_save->setObjectName(QStringLiteral("action_save"));
        action_clear = new QAction(LexicalAnalyzerClass);
        action_clear->setObjectName(QStringLiteral("action_clear"));
        action_analyse = new QAction(LexicalAnalyzerClass);
        action_analyse->setObjectName(QStringLiteral("action_analyse"));
        centralWidget = new QWidget(LexicalAnalyzerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(5, 5, 5, 5);
        splitter_horizontal = new QSplitter(centralWidget);
        splitter_horizontal->setObjectName(QStringLiteral("splitter_horizontal"));
        splitter_horizontal->setOrientation(Qt::Horizontal);
        splitter_horizontal->setChildrenCollapsible(false);
        textEdit_code = new QTextEdit(splitter_horizontal);
        textEdit_code->setObjectName(QStringLiteral("textEdit_code"));
        textEdit_code->setMinimumSize(QSize(523, 0));
        splitter_horizontal->addWidget(textEdit_code);
        splitter_vertical = new QSplitter(splitter_horizontal);
        splitter_vertical->setObjectName(QStringLiteral("splitter_vertical"));
        splitter_vertical->setMinimumSize(QSize(300, 0));
        splitter_vertical->setMaximumSize(QSize(16777215, 16777215));
        splitter_vertical->setOrientation(Qt::Vertical);
        splitter_vertical->setChildrenCollapsible(false);
        tableView_token = new QTableView(splitter_vertical);
        tableView_token->setObjectName(QStringLiteral("tableView_token"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableView_token->sizePolicy().hasHeightForWidth());
        tableView_token->setSizePolicy(sizePolicy);
        splitter_vertical->addWidget(tableView_token);
        tableView_error = new QTableView(splitter_vertical);
        tableView_error->setObjectName(QStringLiteral("tableView_error"));
        tableView_error->setMinimumSize(QSize(0, 100));
        tableView_error->setMaximumSize(QSize(16777215, 200));
        splitter_vertical->addWidget(tableView_error);
        splitter_horizontal->addWidget(splitter_vertical);

        horizontalLayout->addWidget(splitter_horizontal);

        LexicalAnalyzerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LexicalAnalyzerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1000, 23));
        menu_file = new QMenu(menuBar);
        menu_file->setObjectName(QStringLiteral("menu_file"));
        menu_help = new QMenu(menuBar);
        menu_help->setObjectName(QStringLiteral("menu_help"));
        menu_operate = new QMenu(menuBar);
        menu_operate->setObjectName(QStringLiteral("menu_operate"));
        LexicalAnalyzerClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(LexicalAnalyzerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        LexicalAnalyzerClass->setStatusBar(statusBar);
        toolBar = new QToolBar(LexicalAnalyzerClass);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        LexicalAnalyzerClass->addToolBar(Qt::LeftToolBarArea, toolBar);

        menuBar->addAction(menu_file->menuAction());
        menuBar->addAction(menu_operate->menuAction());
        menuBar->addAction(menu_help->menuAction());
        menu_file->addAction(action_new);
        menu_file->addAction(action_open);
        menu_file->addAction(action_save);
        menu_file->addSeparator();
        menu_file->addAction(action_quit);
        menu_help->addAction(action_tokenlist);
        menu_help->addSeparator();
        menu_help->addAction(action_about);
        menu_help->addAction(action_homepage);
        menu_operate->addAction(action_clear);
        menu_operate->addAction(action_analyse);

        retranslateUi(LexicalAnalyzerClass);

        QMetaObject::connectSlotsByName(LexicalAnalyzerClass);
    } // setupUi

    void retranslateUi(QMainWindow *LexicalAnalyzerClass)
    {
        LexicalAnalyzerClass->setWindowTitle(QApplication::translate("LexicalAnalyzerClass", "Lexizer \350\257\215\346\263\225\345\210\206\346\236\220\345\231\250", 0));
        action_open->setText(QApplication::translate("LexicalAnalyzerClass", "\346\211\223\345\274\200", 0));
        action_quit->setText(QApplication::translate("LexicalAnalyzerClass", "\351\200\200\345\207\272", 0));
        action_new->setText(QApplication::translate("LexicalAnalyzerClass", "\346\226\260\345\273\272", 0));
        action_tokenlist->setText(QApplication::translate("LexicalAnalyzerClass", "Token\350\241\250", 0));
        action_about->setText(QApplication::translate("LexicalAnalyzerClass", "\345\205\263\344\272\216", 0));
        action_homepage->setText(QApplication::translate("LexicalAnalyzerClass", "\350\256\277\351\227\256\344\270\273\351\241\265", 0));
        action_save->setText(QApplication::translate("LexicalAnalyzerClass", "\344\277\235\345\255\230", 0));
        action_clear->setText(QApplication::translate("LexicalAnalyzerClass", "\346\270\205\347\251\272", 0));
        action_analyse->setText(QApplication::translate("LexicalAnalyzerClass", "\345\210\206\346\236\220\350\257\215\346\263\225", 0));
        menu_file->setTitle(QApplication::translate("LexicalAnalyzerClass", "\346\226\207\344\273\266", 0));
        menu_help->setTitle(QApplication::translate("LexicalAnalyzerClass", "\345\270\256\345\212\251", 0));
        menu_operate->setTitle(QApplication::translate("LexicalAnalyzerClass", "\346\223\215\344\275\234", 0));
        toolBar->setWindowTitle(QApplication::translate("LexicalAnalyzerClass", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class LexicalAnalyzerClass: public Ui_LexicalAnalyzerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEXICALANALYZER_H
