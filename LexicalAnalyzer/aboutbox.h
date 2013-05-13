#ifndef ABOUT_H
#define ABOUT_H

#include <QtWidgets>

class AboutBox : public QWidget
{
public:
	AboutBox(QWidget *parent) : QWidget(parent)
	{
		setWindowFlags(Qt::Tool);
		setWindowTitle(QStringLiteral("¹ØÓÚ¡°Lexizer ´Ê·¨·ÖÎöÆ÷¡±"));
		setAttribute(Qt::WA_DeleteOnClose);
		setWindowModality(Qt::WindowModal);
		setFixedSize(400, 170);

		QLabel *label_logo = new QLabel(this);
		label_logo->setGeometry(20, 20, 130, 130);
		label_logo->setPixmap(QPixmap(":/img/logo"));

		QFrame *line = new QFrame(this);
		line->setGeometry(QRect(170, label_logo->y(), 3, label_logo->height()));
		line->setFrameShape(QFrame::VLine);
		line->setFrameShadow(QFrame::Sunken);

		QLabel *label_name = new QLabel(this);
		label_name->setGeometry(220, label_logo->y() - 9, 150, 30);
		QFont font_name;
		font_name.setBold(true);
		font_name.setFamily(QStringLiteral("Î¢ÈíÑÅºÚ"));
		font_name.setPixelSize(15);
		label_name->setFont(font_name);
		label_name->setText(QStringLiteral("Lexizer ´Ê·¨·ÖÎöÆ÷"));

		QLabel *label_author = new QLabel(this);
		label_author->setGeometry(216, 58, 110, 60);
		QFont font_author;
		font_author.setBold(true);
		font_author.setFamily(QStringLiteral("Î¢ÈíÑÅºÚ"));
		font_author.setPixelSize(12);
		label_author->setFont(font_author);
		label_author->setText(QStringLiteral("°æ±¾£ºv1.01\nÑ§Éú£ºÄªÓî\nÑ§ºÅ£º1040112115"));

		QLabel *label_copyright = new QLabel(this);
		label_copyright->setGeometry(186, 122, 200, 30);
		QFont font_copyright;
		font_copyright.setFamily(QStringLiteral("Î¢ÈíÑÅºÚ"));
		font_copyright.setPixelSize(9);
		label_copyright->setFont(font_copyright);
		label_copyright->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		label_copyright->setText(QStringLiteral("Copyright \u00a9 2013 Mok's Studio. \nAll Rights Reserved."));
	}
};
#endif // ABOUT_H