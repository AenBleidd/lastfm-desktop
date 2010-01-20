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

#include "MainWindow.h"
#include "MainWidget.h"
#include "widgets/MultiStarterWidget.h"
#include "widgets/PlaybackControlsWidget.h"
#include "widgets/NowPlayingWidget.h"
#include "lib/unicorn/qtwin.h"
#include "lib/unicorn/AnimatedStatusBar.h"
#include "lib/unicorn/widgets/MessageBar.h"
#include <lastfm/RadioStation>
#include <QLineEdit>
#include <QSizeGrip>
#include <QMenuBar>
#include <QPaintEngine>
#include <QPainter>
#include "Radio.h"

MainWindow::MainWindow()
{
    setUnifiedTitleAndToolBarOnMac( true );
    QtWin::extendFrameIntoClientArea( this );

    QStatusBar* status = new QStatusBar( this );
    addDragHandleWidget( status );
    PlaybackControlsWidget* pcw = new PlaybackControlsWidget( status );

    status->setSizeGripEnabled( false );

    status->addWidget( pcw, 1 );
    setStatusBar( status );

    MainWidget* mw;

    QWidget* w = new QWidget();
    
    new QVBoxLayout( w );
    w->layout()->setContentsMargins( 0, 0, 0, 0 );
    w->layout()->addWidget(mw = new MainWidget());

    connect( mw, SIGNAL( widgetChanged(QWidget*)), SLOT( onWidgetChanged( QWidget* )));

    m_messageBar = new MessageBar( w );

    connect(mw, SIGNAL(startRadio(RadioStation)), SIGNAL(startRadio(RadioStation)));

    AuthenticatedUser user;
    connect(user.getFriends(), SIGNAL(finished()), mw, SLOT(onUserGotFriends()));
    connect(user.getTopTags(), SIGNAL(finished()), mw, SLOT(onUserGotTopTags()));
    connect(user.getPlaylists(), SIGNAL(finished()), mw, SLOT(onUserGotPlaylists()));
    connect(user.getRecentStations(), SIGNAL(finished()), mw, SLOT(onUserGotRecentStations()));

    connect(pcw, SIGNAL(startRadio(RadioStation)), mw, SLOT(onStartRadio(RadioStation)));

    setCentralWidget( w );

    finishUi();

    //todo: bury this:
    menuBar()->addMenu("Normania")->addAction( tr("RQL"), mw, SLOT(rawrql()), QKeySequence(tr("Ctrl+r")) );
}

void
MainWindow::onRadioError(int code, const QVariant& data)
{
    switch (code)
    {
        case lastfm::ws::NotEnoughContent:
            m_messageBar->show(tr("Sorry, there is no more content available for this radio station."));
            break;
            
        case lastfm::ws::MalformedResponse:
        case lastfm::ws::TryAgainLater:
            m_messageBar->show(tr("Sorry, there was a radio error at Last.fm. Please try again later."));
            break;
            
        case lastfm::ws::SubscribersOnly:
            m_messageBar->show(tr("Sorry, this station is only available to Last.fm subscribers. "
                           "<A href='http://www.last.fm/subscribe'>Sign up</a>."));
            break;

        case lastfm::ws::UnknownError:
            // string contains Phonon generated user readable error message
            m_messageBar->show(data.toString());
            break;

        default:
            m_messageBar->show("Sorry, an unexpected error occurred.");
            break;
    }
}
