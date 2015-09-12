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
#include "request_p.h"
#include "urls.h"

namespace CuteRadio {

/*!
    \class ResourcesRequest
    \brief Handles requests for cuteRadio resources.
    
    \ingroup requests
    
    The ResourcesRequest class is used for making requests to the cuteRadio Data API that concern 
    cuteRadio resources.
    
    Example usage:
    
    C++
    
    \code
    using namespace CuteRadio;
    
    ...
    
    ResourcesRequest request;
    request.get("/stations");
    connect(&request, SIGNAL(finished()), this, SLOT(onRequestFinished()));
    
    ...
    
    void MyClass::onRequestFinished() {
        if (request.status() == ResourcesRequest::Ready) {            
            QMapIterator<QString, QVariant> iterator(request.result().toMap());
            
            while (iterator.hasNext()) {
                iterator.next();
                qDebug() << iterator.key() << "=" << iterator.value();
            }
        }
        else {
            qDebug() << request.errorString();
        }
    }
    \endcode
    
    QML
    
    \code
    import QtQuick 1.0
    import CuteRadio 1.0
    
    ResourcesRequest {
        id: request

        onFinished: {
            if (status == ResourcesRequest.Ready) {
                for (var att in result) {
                    console.log(att + " = " + result[att]);
                }
            }
            else {
                console.log(errorString);
            }
        }
        
        Component.onCompleted: get("/stations")
    }
    \endcode
    
    For more details about cuteRadio resources, see the cuteRadio reference documentation 
    <a target="_blank" href="https://marxoft.co.uk/doc/cuteradio">here</a>.
*/
ResourcesRequest::ResourcesRequest(QObject *parent) :
    Request(parent)
{
}

/*!
    \brief Requests cuteRadio resource(s) from \a resourcePath.
    
    For example, to search tracks:
    
    \code
    ResourcesRequest request;
    QVariantMap filters;
    filters["limit"] = 10;
    filters["search"] = "Radio";
    request.get("/stations", filters);
    \endcode
*/
void ResourcesRequest::get(const QString &resourcePath, const QVariantMap &filters) {
    QUrl u(QString("%1%2%3").arg(API_URL).arg(resourcePath.startsWith("/") ? QString() : QString("/"))
                            .arg(resourcePath));
#if QT_VERSION >= 0x050000
    if (!filters.isEmpty()) {
        QUrlQuery query(u);
        addUrlQueryItems(&query, filters);
        u.setQuery(query);
    }
#else
    if (!filters.isEmpty()) {
        addUrlQueryItems(&u, filters);
    }
#endif
    setUrl(u);
    setData(QVariant());
    Request::get();
}

/*!
    \brief Inserts a new cuteRadio resource.
    
    For example, to insert a new favourite station on behalf of the authenticated user:
    
    \code
    ResourcesRequest request;
    QVariantMap favourite;
    favourite["stationId"] = 1001;
    request.setAccessToken(USER_ACCESS_TOKEN);
    request.insert(favourite, "/favourites");
    \endcode
*/
void ResourcesRequest::insert(const QVariantMap &resource, const QString &resourcePath) {
    QUrl u(QString("%1%2%3").arg(API_URL).arg(resourcePath.startsWith("/") ? QString() : QString("/"))
                            .arg(resourcePath));
    QString body;
    addPostBody(&body, resource);
    setUrl(u);
    setData(body);
    post();
}

/*!
    \brief Updates the cuteRadio resource at \a resourcePath.
    
    For example, to update an existing station owned by the authenticated user:
    
    \code
    ResourcesRequest request;
    QVariantMap station;
    station["title"] = "New station title";
    station["description"] = "New station description";
    request.setAccessToken(USER_ACCESS_TOKEN);
    request.update("/stations/EXISTING_STATION_ID", station);
    \endcode
*/
void ResourcesRequest::update(const QString &resourcePath, const QVariantMap &resource) {
    QUrl u(QString("%1%2%3").arg(API_URL).arg(resourcePath.startsWith("/") ? QString() : QString("/"))
                            .arg(resourcePath));
    QString body;
    addPostBody(&body, resource);
    setUrl(u);
    setData(body);
    put();
}

/*!
    \brief Deletes the cuteRadio resource at \a resourcePath.
    
    For example, to delete a favourite station on behalf of the authenticated user:
    
    \code
    ResourcesRequest request;
    request.setAccessToken(USER_ACCESS_TOKEN);
    request.del("/favourites/EXISTING_STATION_ID");
    \endcode
*/
void ResourcesRequest::del(const QString &resourcePath) {
    QUrl u(QString("%1%2%3").arg(API_URL).arg(resourcePath.startsWith("/") ? QString() : QString("/"))
                            .arg(resourcePath));
    setUrl(u);
    setData(QVariant());
    deleteResource();
}

}
