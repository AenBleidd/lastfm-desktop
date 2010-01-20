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

#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QImage>
#include <QPixmap>

#include <lastfm/Track>
#include <lastfm/RadioStation>

#include "lib/unicorn/TrackImageFetcher.h"

#include "NowPlayingWidget.h"
#include "RadioProgressBar.h"

NowPlayingWidget::NowPlayingWidget()
{
    new QVBoxLayout( this );

    ui.cover = new QLabel( this );
    ui.cover->setAlignment( Qt::AlignCenter );

    static_cast<QBoxLayout*>(layout())->addStretch();

    layout()->addWidget( ui.cover );

    static_cast<QBoxLayout*>(layout())->addStretch();
    
    ui.track = new QLabel();
    layout()->addWidget( ui.track );
    
    ui.album = new QLabel();
    layout()->addWidget( ui.album );
    
    ui.bar = new RadioProgressBar();
    layout()->addWidget(ui.bar);
    connect( this, SIGNAL( tick( qint64 )), ui.bar, SLOT( onRadioTick( qint64 )));
}

void
NowPlayingWidget::onTuningIn( const RadioStation& )
{
}

void
NowPlayingWidget::onTrackSpooled( const Track& t )
{
    ui.cover->clear();
    TrackImageFetcher* imageFetcher = new TrackImageFetcher( t );
    connect( imageFetcher, SIGNAL( finished( QImage )), SLOT( onImageFinished( QImage )));
    imageFetcher->start();
    
    ui.track->setText( t.artist() + " - " + t.title() );
    if (!t.album().isNull()) {
        ui.album->setText( "from " + t.album().title() );
        ui.album->show();
    } else {
        ui.album->hide();
    }
    ui.bar->onTrackSpooled(t, 0);
    qDebug() << t;
}

void 
NowPlayingWidget::onImageFinished( const QImage& image )
{
    QImage sacledImage = image.scaled( 300, 300, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation );

    QImage cropedImage = sacledImage.copy( (sacledImage.width() - 300) / 2, (sacledImage.height() - 300) / 2, 300, 300 );

    ui.cover->setPixmap( QPixmap::fromImage( cropedImage ) );
    sender()->deleteLater();
}

void
NowPlayingWidget::onBuffering( int )
{
}

void
NowPlayingWidget::onStopped()
{
}
