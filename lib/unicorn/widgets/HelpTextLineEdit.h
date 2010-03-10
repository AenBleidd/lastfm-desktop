/*
   Copyright 2005-2009 Last.fm Ltd. 
      - Primarily authored by Max Howell, Jono Cole and Doug Mansell

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
#ifndef HELP_TEXT_LINE_EDIT_H
#define HELP_TEXT_LINE_EDIT_H

#include <QLineEdit>

#include "lib/DllExportMacro.h"

class UNICORN_DLLEXPORT HelpTextLineEdit : public QLineEdit
{
    QString const m_text;

public:
    HelpTextLineEdit( const QString& helpText = "", QWidget* parent = 0 );
    
protected:
    virtual void paintEvent( QPaintEvent* );
};

#endif
