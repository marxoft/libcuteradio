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

#include "searchesmodel.h"
#include "resourcesmodel_p.h"

namespace CuteRadio {

/*!
    \class SearchesModel
    \brief A model for retrieving station searches
    
    \ingroup models
    
    SearchesModel is used for retrieving station searches, and extends \a ResourcesModel 
    by providing the following data roles:
    
    <table>
        <tr>
        <th>Role</th>
        <th>Role name</th>
        <th>Description</th>
        </tr>
        <tr>
            <td>Qt::DisplayRole/KeywordRole</td>
            <td>name</td>
            <td>The display name of the search.</td>
        </tr>
        <tr>
            <td>CountRole</td>
            <td>count</td>
            <td>The number of times the search keyword has been used.</td>
        </tr>
    </table>
*/
SearchesModel::SearchesModel(QObject *parent) :
    ResourcesModel(parent)
{
    Q_D(ResourcesModel);
    d->resource = QString("searches");
    d->dynamicRoles = false;
    d->roles[Qt::DisplayRole] = "keyword";
    d->roles[KeywordRole] = "keyword";
    d->roles[CountRole] = "count";
#if QT_VERSION < 0x050000
    setRoleNames(d->roles);
#endif
}

int SearchesModel::columnCount(const QModelIndex &) const {
    return 2;
}

QVariant SearchesModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0:
            return ResourcesModel::data(index, KeywordRole);
        case 1:
            return ResourcesModel::data(index, CountRole);
        default:
            break;
        }
    }

    return ResourcesModel::data(index, role);
}

QVariant SearchesModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if ((orientation == Qt::Horizontal) && (role == Qt::DisplayRole)) {
        switch (section) {
        case 0:
            return tr("Keyword");
        case 1:
            return tr("Count");
        default:
            break;
        }
    }

    return QVariant();
}

}
