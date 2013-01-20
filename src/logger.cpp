/****************************************************************************
**
** Jreen
**
** Copyright © 2012 Ruslan Nigmatullin <euroelessar@yandex.ru>
**
*****************************************************************************
**
** $JREEN_BEGIN_LICENSE$
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
** See the GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see http://www.gnu.org/licenses/.
** $JREEN_END_LICENSE$
**
****************************************************************************/

#include "logger.h"

namespace Jreen
{

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0) || QT_DEPRECATED_SINCE(5, 0)
Q_GLOBAL_STATIC(QList<QtMsgHandler>, handlers)

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::addHandler(QtMsgHandler handler)
{
	handlers()->append(handler);
}

void Logger::removeHandler(QtMsgHandler handler)
{
	handlers()->removeOne(handler);
}

bool Logger::isNull()
{
	return handlers()->isEmpty();
}

void Logger::flushDebug(Debug::Stream *stream)
{
	QByteArray data = stream->stream.toLocal8Bit();
	foreach (QtMsgHandler handler, *handlers())
		handler(stream->type, data);
}
#endif

}
