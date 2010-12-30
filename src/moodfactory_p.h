/****************************************************************************
 *  moodfactory_p.h
 *
 *  Copyright (c) 2010 by Sidorov Aleksey <sauron@citadelspb.com>
 *
 ***************************************************************************
 *                                                                         *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************
*****************************************************************************/

#ifndef MOODFACTORY_P_H
#define MOODFACTORY_P_H
#include "stanzaextension.h"
#include "mood.h"
#include "langmap.h"

namespace jreen {

class MoodFactory : public StanzaExtensionFactory<Mood>
{
public:
	MoodFactory();
	virtual ~MoodFactory();
	QStringList features() const;
	bool canParse(const QStringRef &name, const QStringRef &uri, const QXmlStreamAttributes &attributes);
	void handleStartElement(const QStringRef &name, const QStringRef &uri, const QXmlStreamAttributes &attributes);
	void handleEndElement(const QStringRef &name, const QStringRef &uri);
	void handleCharacterData(const QStringRef &text);
	void serialize(StanzaExtension *extension, QXmlStreamWriter *writer);
	StanzaExtension::Ptr createExtension();
private:
	int m_depth;
	Mood::Type m_subtype;
	QString m_text; //may be need to replace by langmap?
};

} // namespace jreen

#endif // MOODFACTORY_P_H