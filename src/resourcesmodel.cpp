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

#include "resourcesmodel.h"
#include "resourcesmodel_p.h"
#include "urls.h"
#ifdef CUTERADIO_DEBUG
#include <QDebug>
#endif

namespace CuteRadio {

/*!
    \class ResourcesModel
    \brief A list model for retrieving cuteRadio resources.
    
    \ingroup models
    
    The ResourcesModel is a list model used for retrieving and displaying cuteRadio resources in a list view. 
    ResourcesModel provides the same methods that are available in ResourcesRequest, so it is better to simply use that
    class if you do not need the additional features provided by a data model.
    
    Roles
    
    The roles and role names of ResourcesModel are created dynamically when the model is populated with data. The roles 
    are created by iterating through the keys of the first item in alphabetical order, starting at Qt::UserRole + 1.
    The role names are the keys themselves.
    
    Example usage:
    
    C++
    
    \code
    using namespace CuteRadio;
    
    ...
    
    QListView *view = new QListView(this);
    ResourcesModel *model = new ResourcesModel(this);
    view->setModel(model);
    
    QVariantMap filters;
    filters["limit"] = 10;
    filters["search"] = "97x";
    filters["language"] = "English";
    filters["sort"] = "playCount";
    filters["sortDescending"] = true;
    model->setResource("stations");
    model->setFilters(filters);
    model->reload();
    \endcode
    
    QML
    
    \code
    import QtQuick 1.0
    import CuteRadio 1.0
    
    ListView {
        id: view
        
        width: 800
        height: 480
        model: ResourcesModel {
            id: resourcesModel
            
            resource: "stations"
            filters: {limit: 10, search: "97x", language: "English", sort: "playCount", sortDescending: true}
        }
        delegate: Text {
            width: view.width
            height: 50
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
            text: title
        }
        
        Component.onCompleted: resourcesModel.reload()
    }
    \endcode
    
    \sa ResourcesRequest
*/

ResourcesModel::ResourcesModel(QObject *parent) :
    Model(*new ResourcesModelPrivate(this), parent)
{
    Q_D(ResourcesModel);

    d->request = new ResourcesRequest(this);
    connect(d->request, SIGNAL(accessTokenChanged()), this, SIGNAL(accessTokenChanged()));
    connect(d->request, SIGNAL(finished()), this, SLOT(_q_onRequestFinished()));
}

/*!
    \property QString ResourcesModel::accessToken
    \brief The access token to be used when making requests to the cuteRadio Data API.
    
    The access token is required when accessing protected resources.
    
    \sa ResourcesRequest::accessToken
*/

/*!
    \fn void ResourcesModel::accessTokenChanged()
    \brief Emitted when the accessToken changes.
*/
QString ResourcesModel::accessToken() const {
    Q_D(const ResourcesModel);
    
    return d->request->accessToken();
}

void ResourcesModel::setAccessToken(const QString &token) {
    Q_D(ResourcesModel);
    
    d->request->setAccessToken(token);
}

/*!
    \property QString ResourcesModel::resource
    \brief The resource type to be retrieved by the model.
    
    Possible values are:
    
    <table>
        <tr>
        <th>Resource</th>
        </tr>
        <tr>
            <td>countries</td>
        </tr>
        <tr>
            <td>favourites</td>
        </tr>
        <tr>
            <td>genres</td>
        </tr>
        <tr>
            <td>languages</td>
        </tr>
        <tr>
            <td>playedstations</td>
        </tr>
        <tr>
            <td>searches</td>
        </tr>
        <tr>
            <td>stations</td>
        </tr>
    </table>
*/
QString ResourcesModel::resource() const {
    Q_D(const ResourcesModel);
    
    return d->resource;
}

void ResourcesModel::setResource(const QString &name) {
    if (name != resource()) {
        Q_D(ResourcesModel);
        d->resource = name;
        emit resourceChanged();
    }
}

/*!
    \property QVariantMap ResourcesModel::filters
    \brief A map of key/value pairs used to filter requests.
*/
QVariantMap ResourcesModel::filters() const {
    Q_D(const ResourcesModel);
    
    return d->filters;
}

void ResourcesModel::setFilters(const QVariantMap &map) {
    Q_D(ResourcesModel);
    
    d->filters = map;
    emit filtersChanged();
}

void ResourcesModel::resetFilters() {
    setFilters(QVariantMap());
}

/*!
    \property enum ResourcesModel::status
    \brief The current status of the model.
    
    \sa ResourcesRequest::status
*/

/*!
    \fn void ResourcesModel::statusChanged()
    \brief Emitted when the status changes.
*/
ResourcesRequest::Status ResourcesModel::status() const {
    Q_D(const ResourcesModel);
    
    return d->request->status();
}

/*!
    \property QVariant ResourcesModel::result
    \brief The current result of the model.
    
    \sa ResourcesRequest::result
*/
QVariant ResourcesModel::result() const {
    Q_D(const ResourcesModel);
    
    return d->request->result();
}

/*!
    \property enum ResourcesModel::error
    \brief The error type of the model.
    
    \sa ResourcesRequest::error
*/
ResourcesRequest::Error ResourcesModel::error() const {
    Q_D(const ResourcesModel);
    
    return d->request->error();
}

/*!
    \property enum ResourcesModel::errorString
    \brief A description of the error of the model.
    
    \sa ResourcesRequest::status
*/
QString ResourcesModel::errorString() const {
    Q_D(const ResourcesModel);
    
    return d->request->errorString();
}

/*!
    \brief Sets the QNetworkAccessManager instance to be used when making requests to the cuteRadio Data API.
    
    ResourcesModel does not take ownership of \a manager.
    
    If no QNetworkAccessManager is set, one will be created when required.
    
    \sa ResourcesRequest::setNetworkAccessManager()
*/
void ResourcesModel::setNetworkAccessManager(QNetworkAccessManager *manager) {
    Q_D(ResourcesModel);
    
    d->request->setNetworkAccessManager(manager);
}

bool ResourcesModel::canFetchMore(const QModelIndex &) const {
    if (status() == ResourcesRequest::Loading) {
        return false;
    }
    
    Q_D(const ResourcesModel);
    
    return !d->next.isEmpty();
}

void ResourcesModel::fetchMore(const QModelIndex &) {
    if (canFetchMore()) {
        Q_D(ResourcesModel);
        
        d->request->get(d->next);
        emit statusChanged(d->request->status());
    }
}

/*!
    \brief Cancels the current request.
    
    \sa ResourcesRequest::cancel()
*/
void ResourcesModel::cancel() {
    Q_D(ResourcesModel);
    
    if (d->request) {
        d->request->cancel();
    }
}

/*!
    \brief Clears any existing data and retreives a new list of cuteRadio resources using the existing properties.
*/
void ResourcesModel::reload() {
    if (status() != ResourcesRequest::Loading) {
        Q_D(ResourcesModel);
        d->next = QString();
        d->previous = QString();
        clear();
        
        if (d->dynamicRoles) {
            d->roles.clear();
        }
        
        d->request->get(d->resource.startsWith('/') ? d->resource : "/" + d->resource, d->filters);
        emit statusChanged(d->request->status());
    }
}

ResourcesModelPrivate::ResourcesModelPrivate(ResourcesModel *parent) :
    ModelPrivate(parent),
    request(0),
    resource("stations"),
    dynamicRoles(true)
{
}
    
void ResourcesModelPrivate::_q_onRequestFinished() {
    if (!request) {
        return;
    }

    Q_Q(ResourcesModel);

    if (request->status() == ResourcesRequest::Ready) {
        const QVariantMap result = request->result().toMap();
    
        if (!result.isEmpty()) {
            next = result.value("next").toString();
            previous = result.value("previous").toString();
        
            const QVariantList list = result.value("items").toList();
        
            if (!list.isEmpty()) {
                if (roles.isEmpty()) {
                    setRoleNames(list.first().toMap());
                }
                
                q->beginInsertRows(QModelIndex(), items.size(), items.size() + list.size() - 1);
                
                foreach (const QVariant &item, list) {
                    items << item.toMap();
                }
                
                q->endInsertRows();
                emit q->countChanged(q->rowCount());
            }
        }
    }
        
    emit q->statusChanged(request->status());
}

}

#include "moc_resourcesmodel.cpp"
