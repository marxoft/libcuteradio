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
#include "model_p.h"

namespace CuteRadio {

class ResourcesModelPrivate : public ModelPrivate
{

public:
    ResourcesModelPrivate(ResourcesModel *parent);
    
    void _q_onRequestFinished();
    
    ResourcesRequest *request;
    
    QString resource;
    QVariantMap filters;
        
    QString next;
    QString previous;
    
    bool dynamicRoles;
    
    Q_DECLARE_PUBLIC(ResourcesModel)
};

}
