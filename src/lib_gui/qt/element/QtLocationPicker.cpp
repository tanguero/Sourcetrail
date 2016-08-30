#include "qt/element/QtLocationPicker.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QStyleOption>

QtLocationPicker::QtLocationPicker(QWidget *parent)
	: QWidget(parent)
	, m_pickDirectory(false)
{
	setObjectName("picker");

	QBoxLayout* layout = new QHBoxLayout();
	layout->setSpacing(0);
	layout->setContentsMargins(1, 1, 1, 1);
	layout->setAlignment(Qt::AlignTop);

	m_data = new QtLineEdit(this);
	m_data->setAttribute(Qt::WA_MacShowFocusRect, 0);
	m_data->setObjectName("locationField");
	layout->addWidget(m_data);

	m_button = new QPushButton("");
	m_button->setObjectName("dotsButton");
	m_button->setToolTip("pick file");
	m_button->setAttribute(Qt::WA_LayoutUsesWidgetRect); // fixes layouting on Mac
	connect(m_button, SIGNAL(clicked()), this, SLOT(handleButtonPress()));
	layout->addWidget(m_button);

	setLayout(layout);
	setSizePolicy(sizePolicy().horizontalPolicy(), QSizePolicy::Fixed);
}

void QtLocationPicker::paintEvent(QPaintEvent*)
{
	QStyleOption opt;
	opt.init(this);

	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void QtLocationPicker::setPlaceholderText(QString text)
{
	m_data->setPlaceholderText(text);
}

QString QtLocationPicker::getText()
{
	return m_data->text();
}

void QtLocationPicker::setText(QString text)
{
	m_data->setText(text);
}

void QtLocationPicker::clearText()
{
	m_data->clear();
}

void QtLocationPicker::setPickDirectory(bool pickDirectory)
{
	m_pickDirectory = pickDirectory;
}

void QtLocationPicker::setFileFilter(const QString& fileFilter)
{
	m_fileFilter = fileFilter;
}

void QtLocationPicker::handleButtonPress()
{
	QString fileName;
	if (m_pickDirectory)
	{
		fileName = QFileDialog::getExistingDirectory(this, tr("Select Directory"), m_data->text());
	}
	else
	{
		fileName = QFileDialog::getOpenFileName(this, tr("Open File"), m_data->text(), m_fileFilter);
	}

	if (!fileName.isEmpty())
	{
		m_data->setText(fileName);
		emit locationPicked();
	}
}
