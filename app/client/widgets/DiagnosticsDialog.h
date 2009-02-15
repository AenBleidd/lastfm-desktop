/***************************************************************************
 *   Copyright 2005-2009 Last.fm Ltd.                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Steet, Fifth Floor, Boston, MA  02110-1301, USA.          *
 ***************************************************************************/

#ifndef DIAGNOSTICS_DIALOG_H
#define DIAGNOSTICS_DIALOG_H

#include "lib/lastfm/global.h"
#include "ui_DiagnosticsDialog.h"
#include <QDateTime>
#include <QPointer>
#include <QProcess> //Qt enums
#include <QFile>


class DiagnosticsDialog : public QDialog
{
    Q_OBJECT

    Ui::DiagnosticsDialog ui;
    class DelayedLabelText* m_delay;

public:
    DiagnosticsDialog( QWidget *parent = 0 );
    
public slots:
    void fingerprinted( const Track& );
    void scrobbleActivity( int );

private slots:
    void onScrobblePointReached();
    
private:
	void scrobbleIPod( bool isManual = false );
	QString diagnosticInformation();

    QPointer<QProcess> m_twiddly;
    QFile* m_ipod_log;

private slots:
	void onScrobbleIPodClicked();
	void onSendLogsClicked();
	void poll();
    void onTwiddlyFinished( int, QProcess::ExitStatus );
    void onTwiddlyError( QProcess::ProcessError );
};


#include <QTimer>
class DelayedLabelText : public QObject
{
    Q_OBJECT
    
    QList<QString> texts;
    QTimer m_timer;
    
public:
    DelayedLabelText( QLabel* parent ) : QObject( parent )
    {
        m_timer.setInterval( 2000 );
        connect( &m_timer, SIGNAL(timeout()), SLOT(timeout()) );
    }
    
    void add( QString text )
    {       
        QLabel* label = static_cast<QLabel*>(parent());

        if (m_timer.isActive()) {
            if (texts.isEmpty() || texts.last() != text)
                texts += text;
            return;
        }
        
        label->setText( text );
        m_timer.start();
    }
    
private slots:
    void timeout()
    {
        if (texts.size())
            static_cast<QLabel*>(parent())->setText( texts.takeFirst() );
        if (texts.isEmpty())
            m_timer.stop();
    }
};


#endif //DIAGNOSTICS_DIALOG_H
