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

#ifndef CUTERADIO_GENRESMODEL_H
#define CUTERADIO_GENRESMODEL_H

#include "resourcesmodel.h"

namespace CuteRadio {

class CUTERADIOSHARED_EXPORT GenresModel : public ResourcesModel
{
    Q_OBJECT
        
    Q_ENUMS(Roles)
    
public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        CountRole
    };
    
    explicit GenresModel(QObject *parent = 0);

private:
    Q_DISABLE_COPY(GenresModel);
};

}

#endif // CUTERADIO_GENRESMODEL_H
