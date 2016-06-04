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

#ifndef CUTERADIO_LANGUAGESMODEL_H
#define CUTERADIO_LANGUAGESMODEL_H

#include "resourcesmodel.h"

namespace CuteRadio {

class CUTERADIOSHARED_EXPORT LanguagesModel : public ResourcesModel
{
    Q_OBJECT
        
    Q_ENUMS(Roles)
    
public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        CountRole
    };
    
    explicit LanguagesModel(QObject *parent = 0);

    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    QVariant headerData(int section, Qt::Orientation orientation = Qt::Horizontal, int role = Qt::DisplayRole) const;

private:
    Q_DISABLE_COPY(LanguagesModel);
};

}

#endif // CUTERADIO_LANGUAGESMODEL_H
