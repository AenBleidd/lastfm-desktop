/*
   Copyright 2005-2009 Last.fm Ltd. 
      - Primarily authored by Jono Cole

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
#ifndef BOOTSTRAP_WIZARD_H
#define BOOTSTRAP_WIZARD_H

#include <QWizardPage>
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QRadioButton>
#include <QNetworkReply>
#include <QPointer>

#include "lib/unicorn/Updater/PluginList.h"
#include "../Application.h"

class BootstrapPage: public QWizardPage
{
    Q_OBJECT

private:
    Q_PROPERTY( QString playerId READ playerId WRITE setPlayerId )

    struct
    {
        class QLabel* description;
    } ui;

public:
    BootstrapPage( QWidget* parent = 0 );

    QString playerId() const { return m_playerId; }
    void setPlayerId( const QString& playerId ) { m_playerId = playerId; }

private:
    void initializePage();
    bool validatePage();
    void cleanupPage();

signals:
    void playerChanged();

private slots:
    void playerSelected();
    
protected:
    PluginList m_pluginList;
    QString m_playerId;
};

#endif //BOOTSTRAP_WIZARD_H
