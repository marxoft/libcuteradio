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

#include "stationsmodel.h"
#include "resourcesmodel_p.h"

namespace CuteRadio {

/*!
    \class StationsModel
    \brief A model for retrieving station stations
    
    \ingroup models
    
    StationsModel is used for retrieving stations (including favourites and played stations), and extends 
    \a ResourcesModel by providing the following data roles:
    
    <table>
        <tr>
        <th>Role</th>
        <th>Role name</th>
        <th>Description</th>
        </tr>
        <tr>
            <td>Qt::DisplayRole/TitleRole</td>
            <td>title</td>
            <td>The display title of the station.</td>
        </tr>
        <tr>
            <td>IdRole</td>
            <td>id</td>
            <td>The station id.</td>
        </tr>
        <tr>
            <td>DescriptionRole</td>
            <td>description</td>
            <td>The station description.</td>
        </tr>
        <tr>
            <td>GenreRole</td>
            <td>genre</td>
            <td>The station genre.</td>
        </tr>
        <tr>
            <td>CountryRole</td>
            <td>country</td>
            <td>The station country.</td>
        </tr>
        <tr>
            <td>LanguageRole</td>
            <td>language</td>
            <td>The station language.</td>
        </tr>
        <tr>
            <td>SourceRole</td>
            <td>source</td>
            <td>The station stream source.</td>
        </tr>
        <tr>
            <td>PlayCountRole</td>
            <td>playCount</td>
            <td>The number of times the station has been played.</td>
        </tr>
        <tr>
            <td>LastPlayedRole</td>
            <td>lastPlayed</td>
            <td>The datetime at which the station was last played.</td>
        </tr>
        <tr>
            <td>CreatorIdRole</td>
            <td>creatorId</td>
            <td>The id of the user that created the station.</td>
        </tr>
        <tr>
            <td>ApprovedRole</td>
            <td>approved</td>
            <td>Whether the station has been approved by moderator/admin.</td>
        </tr>
        <tr>
            <td>FavouriteRole</td>
            <td>favourite</td>
            <td>Whether the station is in the authenticated user's favourites.</td>
        </tr>
    </table>
*/
StationsModel::StationsModel(QObject *parent) :
    ResourcesModel(parent)
{
    Q_D(ResourcesModel);
    d->resource = QString("stations");
    d->dynamicRoles = false;
    d->roles[Qt::DisplayRole] = "title";
    d->roles[IdRole] = "id";
    d->roles[TitleRole] = "title";
    d->roles[DescriptionRole] = "description";
    d->roles[GenreRole] = "genre";
    d->roles[CountryRole] = "country";
    d->roles[LanguageRole] = "language";
    d->roles[SourceRole] = "source";
    d->roles[PlayCountRole] = "playCount";
    d->roles[LastPlayedRole] = "lastPlayed";
    d->roles[CreatorIdRole] = "creatorId";
    d->roles[ApprovedRole] = "approved";
    d->roles[FavouriteRole] = "favourite";
#if QT_VERSION < 0x050000
    setRoleNames(d->roles);
#endif
}

int StationsModel::columnCount(const QModelIndex &) const {
    return 4;
}

QVariant StationsModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0:
            return ResourcesModel::data(index, TitleRole);
        case 1:
            return ResourcesModel::data(index, GenreRole);
        case 2:
            return ResourcesModel::data(index, CountryRole);
        case 3:
            return ResourcesModel::data(index, LanguageRole);
        default:
            break;
        }
    }

    return ResourcesModel::data(index, role);
}

QVariant StationsModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if ((orientation == Qt::Horizontal) && (role == Qt::DisplayRole)) {
        switch (section) {
        case 0:
            return tr("Title");
        case 1:
            return tr("Genre");
        case 2:
            return tr("Country");
        case 3:
            return tr("Language");
        default:
            break;
        }
    }

    return QVariant();
}

}
