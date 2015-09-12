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

#include "plugin.h"
#include "countriesmodel.h"
#include "genresmodel.h"
#include "languagesmodel.h"
#include "resourcesmodel.h"
#include "resourcesrequest.h"
#include "searchesmodel.h"
#include "stationsmodel.h"
#if QT_VERSION >= 0x050000
#include <qqml.h>
#else
#include <qdeclarative.h>
#endif

namespace CuteRadio {

void Plugin::registerTypes(const char *uri) {
    Q_ASSERT(uri == QLatin1String("CuteRadio"));
    
    qmlRegisterType<CountriesModel>(uri, 1, 0, "CountriesModel");
    qmlRegisterType<GenresModel>(uri, 1, 0, "GenresModel");
    qmlRegisterType<LanguagesModel>(uri, 1, 0, "LanguagesModel");
    qmlRegisterType<ResourcesModel>(uri, 1, 0, "ResourcesModel");
    qmlRegisterType<ResourcesRequest>(uri, 1, 0, "ResourcesRequest");
    qmlRegisterType<SearchesModel>(uri, 1, 0, "SearchesModel");
    qmlRegisterType<StationsModel>(uri, 1, 0, "StationsModel");
}

}

QML_DECLARE_TYPE(CuteRadio::CountriesModel)
QML_DECLARE_TYPE(CuteRadio::GenresModel)
QML_DECLARE_TYPE(CuteRadio::LanguagesModel)
QML_DECLARE_TYPE(CuteRadio::ResourcesModel)
QML_DECLARE_TYPE(CuteRadio::ResourcesRequest)
QML_DECLARE_TYPE(CuteRadio::SearchesModel)
QML_DECLARE_TYPE(CuteRadio::StationsModel)
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(cuteradioplugin, CuteRadio::Plugin)
#endif
