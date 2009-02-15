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

#include "lib/lastfm/global.h"
#include <QWidget>


class RadioProgressBar : public QWidget
{
    Q_OBJECT

public:
    RadioProgressBar( QWidget* parent = 0 );
    
    virtual void paintEvent( QPaintEvent* e );
    virtual QSize sizeHint() const;
    
private slots:
    void onRadioTick( qint64 tick );
    void onTrackSpooled( const Track& track, class StopWatch* );

private:
    int m_scrobbleProgressTick;
    int m_currentTrackDuration;
    
    struct {
        class QLabel* time;
        class QLabel* timeToGo;
    } ui;
};
