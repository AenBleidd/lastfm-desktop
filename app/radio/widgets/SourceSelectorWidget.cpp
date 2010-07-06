/*
   Copyright 2005-2009 Last.fm Ltd. 

   This file is part of the Last.fm Desktop Application Suite.

   lastfm-desktop is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   lastfm-desktop is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with lastfm-desktop.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QListWidgetItem>
#include <QCompleter>
#include "SourceSelectorListWidget.h"
#include "SourceSelectorWidget.h"


SourceSelectorWidget::SourceSelectorWidget(QLineEdit* edit, QWidget* parent)
    :StylableWidget(parent)
{
    QGridLayout* grid = new QGridLayout(this);

    m_edit = edit;
    m_edit->setParent(this);

    grid->setContentsMargins( 0, 0, 0, 0 );
    grid->addWidget(m_edit, 0, 0);

    m_button = new QPushButton(tr("Add"));
    m_button->setToolTip( tr( "Add source" ) );
    grid->addWidget(m_button, 0, 1);
    grid->setColumnStretch(0, 3);
    onTextChanged(m_edit->text());

    m_list = new SourceSelectorListWidget();
    m_list->setIconSize(QSize(0,0));
    m_list->setTextElideMode(Qt::ElideRight);
    m_list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_list->setDragEnabled( true );
    grid->addWidget(m_list, 1, 0, 1, 2);

    connect(m_edit, SIGNAL(returnPressed()), SLOT(emitAdd())); 
    connect(m_edit, SIGNAL(textChanged(QString)), SLOT(onTextChanged(QString)));
    connect(m_edit->completer(), SIGNAL(activated(QString)), SLOT(onCompleterActivated(QString)));

    connect(m_button, SIGNAL(clicked()), SLOT(emitAdd()));
    connect(m_list, SIGNAL(itemClicked(QListWidgetItem *)), SIGNAL(itemClicked(QListWidgetItem *)));
}

QListWidget* 
SourceSelectorWidget::list()
{
    return m_list;
}

void
SourceSelectorWidget::onTextChanged(const QString& text)
{
    m_button->setEnabled( text.length() != 0 );
}

void
SourceSelectorWidget::emitAdd()
{
    emit add(m_edit->text());
}

void
SourceSelectorWidget::onCompleterActivated(const QString& text)
{
    m_edit->setText(text);
    emit add(text);
}
