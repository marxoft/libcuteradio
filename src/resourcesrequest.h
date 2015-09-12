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
 
#ifndef CUTERADIO_RESOURCESREQUEST_H
#define CUTERADIO_RESOURCESREQUEST_H

#include "request.h"

namespace CuteRadio {

class CUTERADIOSHARED_EXPORT ResourcesRequest : public Request
{
    Q_OBJECT
    
public:
    explicit ResourcesRequest(QObject *parent = 0);
    
public Q_SLOTS:    
    void get(const QString &resourcePath, const QVariantMap &filters = QVariantMap());
        
    void insert(const QVariantMap &resource, const QString &resourcePath);
    
    void update(const QString &resourcePath, const QVariantMap &resource);
    
    void del(const QString &resourcePath);
    
private:
    Q_DISABLE_COPY(ResourcesRequest)
};

}

#endif // CUTERADIO_RESOURCESREQUEST_H
