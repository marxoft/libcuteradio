/*
 * Copyright (C) 2015 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CUTERADIO_URLS_H
#define CUTERADIO_URLS_H

#include <QString>

namespace CuteRadio {

static const QString API_URL("http://marxoft.co.uk/api/cuteradio");

static const QString COUNTRIES_URL(API_URL + "/countries");
static const QString FAVOURITES_URL(API_URL + "/favourites");
static const QString GENRES_URL(API_URL + "/genres");
static const QString LANGUAGES_URL(API_URL + "/languages");
static const QString PLAYED_STATIONS_URL(API_URL + "/playedstations");
static const QString SEARCHES_URL(API_URL + "/searches");
static const QString STATIONS_URL(API_URL + "/stations");
static const QString TOKEN_URL(API_URL + "/token");

}

#endif // CUTERADIO_URLS_H
