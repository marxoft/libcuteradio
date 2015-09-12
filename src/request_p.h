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

#ifndef CUTERADIO_REQUEST_P_H
#define CUTERADIO_REQUEST_P_H

#include "request.h"
#include "json.h"
#include <QUrl>
#include <QVariantMap>
#include <QNetworkRequest>
#if QT_VERSION >= 0x050000
#include <QUrlQuery>
#endif
#ifdef CUTERADIO_DEBUG
#include <QDebug>
#endif

class QNetworkReply;

namespace CuteRadio {

static const int MAX_REDIRECTS = 8;

#if QT_VERSION >= 0x050000
inline void addUrlQueryItems(QUrlQuery *query, const QVariantMap &map) {
#ifdef CUTERADIO_DEBUG
    qDebug() << "addUrlQueryItems:" << query << map;
#endif
    QMapIterator<QString, QVariant> iterator(map);
    QByteArray value;
    
    while (iterator.hasNext()) {
        iterator.next();
        
        switch (iterator.value().type()) {
        case QVariant::String:
        case QVariant::ByteArray:
            value = iterator.value().toString().toUtf8();
            break;
        default:
            value = QtJson::Json::serialize(iterator.value());
            break;
        }
        
        query->addQueryItem(iterator.key(), value);
    }
}

inline void addRequestHeaders(QNetworkRequest *request, const QVariantMap &map) {
#ifdef CUTERADIO_DEBUG
    qDebug() << "addRequestHeaders:" << request->url() << map;
#endif
    QMapIterator<QString, QVariant> iterator(map);
    QByteArray value;
    
    while (iterator.hasNext()) {
        iterator.next();
        
        switch (iterator.value().type()) {
        case QVariant::String:
        case QVariant::ByteArray:
            value = iterator.value().toString().toUtf8();
            break;
        default:
            value = QtJson::Json::serialize(iterator.value());
            break;
        }
        
        request->setRawHeader(iterator.key().toUtf8(), value);
    }
}

inline void addPostBody(QString *body, const QVariantMap &map) {
#ifdef CUTERADIO_DEBUG
    qDebug() << "addPostBody:" << body << map;
#endif
    QMapIterator<QString, QVariant> iterator(map);
    QByteArray value;
    
    while (iterator.hasNext()) {
        iterator.next();
        
        switch (iterator.value().type()) {
        case QVariant::String:
        case QVariant::ByteArray:
            value = iterator.value().toString().toUtf8();
            break;
        default:
            value = QtJson::Json::serialize(iterator.value());
            break;
        }
        
        body->append(iterator.key() + "=" + value);
        
        if (iterator.hasNext()) {
            body->append("&");
        }
    }
}
#else
inline void addUrlQueryItems(QUrl *url, const QVariantMap &map) {
#ifdef CUTERADIO_DEBUG
    qDebug() << "addUrlQueryItems:" << url << map;
#endif
    QMapIterator<QString, QVariant> iterator(map);
    QByteArray value;
    
    while (iterator.hasNext()) {
        iterator.next();
        
        switch (iterator.value().type()) {
        case QVariant::String:
        case QVariant::ByteArray:
            value = iterator.value().toString().toUtf8();
            break;
        case QVariant::Double: // In QtQuick 1.x, integers declared in JS are passed as doubles.
            value = QByteArray::number(iterator.value().toInt());
            break;
        default:
            value = QtJson::Json::serialize(iterator.value());
            break;
        }
        
        url->addQueryItem(iterator.key(), value);
    }
}

inline void addRequestHeaders(QNetworkRequest *request, const QVariantMap &map) {
#ifdef CUTERADIO_DEBUG
    qDebug() << "addRequestHeaders:" << request->url() << map;
#endif
    QMapIterator<QString, QVariant> iterator(map);
    QByteArray value;
    
    while (iterator.hasNext()) {
        iterator.next();
        
        switch (iterator.value().type()) {
        case QVariant::String:
        case QVariant::ByteArray:
            value = iterator.value().toString().toUtf8();
            break;
        case QVariant::Double: // In QtQuick 1.x, integers declared in JS are passed as doubles.
            value = QByteArray::number(iterator.value().toInt());
            break;
        default:
            value = QtJson::Json::serialize(iterator.value());
            break;
        }
        
        request->setRawHeader(iterator.key().toUtf8(), value);
    }
}

inline void addPostBody(QString *body, const QVariantMap &map) {
#ifdef CUTERADIO_DEBUG
    qDebug() << "addPostBody:" << body << map;
#endif
    QMapIterator<QString, QVariant> iterator(map);
    QByteArray value;
    
    while (iterator.hasNext()) {
        iterator.next();
        
        switch (iterator.value().type()) {
        case QVariant::String:
        case QVariant::ByteArray:
            value = iterator.value().toString().toUtf8();
            break;
        case QVariant::Double: // In QtQuick 1.x, integers declared in JS are passed as doubles.
            value = QByteArray::number(iterator.value().toInt());
            break;
        default:
            value = QtJson::Json::serialize(iterator.value());
            break;
        }
        
        body->append(iterator.key() + "=" + value);
        
        if (iterator.hasNext()) {
            body->append("&");
        }
    }
}
#endif

class RequestPrivate
{

public:
    RequestPrivate(Request *parent);
    virtual ~RequestPrivate();
    
    QNetworkAccessManager* networkAccessManager();
    
    void setOperation(Request::Operation op);
    
    void setStatus(Request::Status s);
    
    void setError(Request::Error e);
    
    void setErrorString(const QString &es);
    
    void setResult(const QVariant &res);
    
    virtual QNetworkRequest buildRequest(bool authRequired = true);
    virtual QNetworkRequest buildRequest(QUrl u, bool authRequired = true);
    
    virtual void followRedirect(const QUrl &redirect);
        
    virtual void _q_onReplyFinished();
    
    Request *q_ptr;
    
    QNetworkAccessManager *manager;
    
    QNetworkReply *reply;
    
    bool ownNetworkAccessManager;
    
    QString accessToken;
        
    QUrl url;
    
    QVariantMap headers;
    
    QVariant data;
    
    QVariant result;
    
    Request::Operation operation;
    
    Request::Status status;
    
    Request::Error error;
    
    QString errorString;
    
    int redirects;
    
    Q_DECLARE_PUBLIC(Request)
};

}

#endif // CUTERADIO_REQUEST_P_H
