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
#ifndef MESSAGE_BAR_H
#define MESSAGE_BAR_H

#include <QWidget>
#include "lib/DllExportMacro.h"

/** @author <max@last.fm> */

class UNICORN_DLLEXPORT MessageBar : public QWidget
{
    Q_OBJECT
    
    class QTimeLine* m_timeline;

    struct Ui {
        QWidget* papyrus;
    } ui;
    
    virtual void resizeEvent( QResizeEvent* );
    void doLayout();
    
public:
    /** Parent should be the widget that the messagebar is added to.
        It should not be added to a layout. */
    MessageBar( QWidget* parent );

    bool eventFilter( QObject* obj, QEvent *event );
    
public slots:
    void show( QWidget* );
    void show( const QString&, const QString& id = QString() );
    void remove( const QString& id );
    
private slots:
    void animate( int );
    void onLabelDestroyed();
};

#endif
