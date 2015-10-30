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

#ifndef CUTERADIO_GLOBAL_H
#define CUTERADIO_GLOBAL_H

#include <qglobal.h>

#if defined(CUTERADIO_LIBRARY)
#  define CUTERADIOSHARED_EXPORT Q_DECL_EXPORT
#elif defined(CUTERADIO_STATIC_LIBRARY)
# define CUTERADIOSHARED_EXPORT
#else
#  define CUTERADIOSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CUTERADIO_GLOBAL_H
