/*
 * Copyright (C) 2015 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "resourcesrequest.h"
#include "json.h"
#include <QCoreApplication>
#include <QStringList>
#include <QSettings>
#include <QDebug>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    app.setOrganizationName("CuteRadio");
    app.setApplicationName("CuteRadio");
    
    QStringList args = app.arguments();
    
    if (args.size() < 3) {
        qWarning() << "Usage: resources-insert RESOURCE RESOURCEPATH";
        return 0;
    }
    
    args.removeFirst();

    QSettings settings;

    CuteRadio::ResourcesRequest request;
    request.setAccessToken(settings.value("Authentication/accessToken").toString());
    
    QVariantMap resource = QtJson::Json::parse(args.takeFirst()).toMap();
    QString resourcePath = args.takeFirst();
    request.insert(resource, resourcePath);

    QObject::connect(&request, SIGNAL(finished()), &app, SLOT(quit()));

    return app.exec();
}
