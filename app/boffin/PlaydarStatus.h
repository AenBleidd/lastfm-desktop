/***************************************************************************
 *   Copyright 2009 Last.fm Ltd.                                           *
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
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#ifndef PLAYDAR_STATUS_H
#define PLAYDAR_STATUS_H

#include <QObject>
#include "PlaydarApi.h"


class WsAccessManager;

class PlaydarStatus : public QObject
{
    Q_OBJECT

public:
    PlaydarStatus(WsAccessManager* wam, PlaydarApi& api);

    void start();

signals:
    void changed(QString newStatusMessage);
    void authed();
    void connected();

private slots:
    void onStat(QString name, QString version, QString hostname, bool bAuthenticated);
    void onAuth(QString authToken);
    void onError();

private:
    void updateText();

    enum State
    {
        Connecting, NotPresent, Authorising, Authorised, NotAuthorised
    };

    State m_state;
    QString m_name;
    QString m_version;
    QString m_hostname;

    WsAccessManager* m_wam;
    PlaydarApi& m_api;
};

#endif

