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

#ifndef CUTERADIO_RESOURCESMODEL_H
#define CUTERADIO_RESOURCESMODEL_H

#include "model.h"
#include "resourcesrequest.h"

namespace CuteRadio {

class ResourcesModelPrivate;

class CUTERADIOSHARED_EXPORT ResourcesModel : public Model
{
    Q_OBJECT
    
    Q_PROPERTY(bool canFetchMore READ canFetchMore NOTIFY statusChanged)
    Q_PROPERTY(QString accessToken READ accessToken WRITE setAccessToken NOTIFY accessTokenChanged)
    Q_PROPERTY(QString resource READ resource WRITE setResource NOTIFY resourceChanged)
    Q_PROPERTY(QVariantMap filters READ filters WRITE setFilters RESET resetFilters NOTIFY filtersChanged)
    Q_PROPERTY(CuteRadio::ResourcesRequest::Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(QVariant result READ result NOTIFY statusChanged)
    Q_PROPERTY(CuteRadio::ResourcesRequest::Error error READ error NOTIFY statusChanged)
    Q_PROPERTY(QString errorString READ errorString NOTIFY statusChanged)
    
    Q_ENUMS(CuteRadio::ResourcesRequest::Status CuteRadio::ResourcesRequest::Error)
                
public: 
    explicit ResourcesModel(QObject *parent = 0);

    QString accessToken() const;
    void setAccessToken(const QString &token);
    
    QString resource() const;
    void setResource(const QString &name);
    
    QVariantMap filters() const;
    void setFilters(const QVariantMap &map);
    void resetFilters();

    ResourcesRequest::Status status() const;
    
    QVariant result() const;
    
    ResourcesRequest::Error error() const;
    QString errorString() const;
    
    void setNetworkAccessManager(QNetworkAccessManager *manager);
    
    bool canFetchMore(const QModelIndex &parent = QModelIndex()) const;
    Q_INVOKABLE void fetchMore(const QModelIndex &parent = QModelIndex());
    
public Q_SLOTS:
    void cancel();
    void reload();
    
Q_SIGNALS:
    void accessTokenChanged();
    void resourceChanged();
    void filtersChanged();
    void statusChanged(CuteRadio::ResourcesRequest::Status status);
    
protected:        
    Q_DECLARE_PRIVATE(ResourcesModel)
    
    Q_PRIVATE_SLOT(d_func(), void _q_onRequestFinished())

private:
    Q_DISABLE_COPY(ResourcesModel)
};

}

#endif // CUTERADIO_RESOURCESMODEL_H
