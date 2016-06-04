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

#include "countriesmodel.h"
#include "resourcesmodel_p.h"

namespace CuteRadio {

/*!
    \class CountriesModel
    \brief A model for retrieving station countries
    
    \ingroup models
    
    CountriesModel is used for retrieving station countries, and extends \a ResourcesModel 
    by providing the following data roles:
        
    <table>
        <tr>
        <th>Role</th>
        <th>Role name</th>
        <th>Description</th>
        </tr>
        <tr>
            <td>Qt::DisplayRole/NameRole</td>
            <td>name</td>
            <td>The display name of the country.</td>
        </tr>
        <tr>
            <td>CountRole</td>
            <td>count</td>
            <td>The number of stations belonging to the country.</td>
        </tr>
    </table>
*/
CountriesModel::CountriesModel(QObject *parent) :
    ResourcesModel(parent)
{
    Q_D(ResourcesModel);
    d->resource = QString("countries");
    d->dynamicRoles = false;
    d->roles[Qt::DisplayRole] = "name";
    d->roles[NameRole] = "name";
    d->roles[CountRole] = "count";
#if QT_VERSION < 0x050000
    setRoleNames(d->roles);
#endif
}

int CountriesModel::columnCount(const QModelIndex &) const {
    return 2;
}

QVariant CountriesModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0:
            return ResourcesModel::data(index, NameRole);
        case 1:
            return ResourcesModel::data(index, CountRole);
        default:
            break;
        }
    }

    return ResourcesModel::data(index, role);
}

QVariant CountriesModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if ((orientation == Qt::Horizontal) && (role == Qt::DisplayRole)) {
        switch (section) {
        case 0:
            return tr("Name");
        case 1:
            return tr("Stations");
        default:
            break;
        }
    }

    return QVariant();
}

}
