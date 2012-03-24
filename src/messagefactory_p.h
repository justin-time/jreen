/****************************************************************************
**
** Jreen
**
** Copyright © 2011 Aleksey Sidorov <gorthauer87@yandex.ru>
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

#ifndef MESSAGEFACTORY_P_H
#define MESSAGEFACTORY_P_H

#include "stanzafactory_p.h"
#include "message.h"

namespace Jreen
{
class JREEN_AUTOTEST_EXPORT MessageFactory : public StanzaFactory
{
public:
	enum State { AtMessage, AtBody, AtSubject,AtThread };
	MessageFactory(Client *client);
	int stanzaType();
	Stanza::Ptr createStanza();
	void serialize(Stanza *stanza, QXmlStreamWriter *writer);
	bool canParse(const QStringRef &name, const QStringRef &uri, const QXmlStreamAttributes &attributes);
	void handleStartElement(const QStringRef &name, const QStringRef &uri, const QXmlStreamAttributes &attributes);
	void handleEndElement(const QStringRef &name, const QStringRef &uri);
	void handleCharacterData(const QStringRef &name);
private:
	void clear();
	int m_depth;
	Message::Type m_subtype;
	LangMap m_body;
	LangMap m_subject;
	State m_state;
	QStringRef m_thread;
};

} // namespace  Jreen

#endif // MESSAGEFACTORY_P_H
