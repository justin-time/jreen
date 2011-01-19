/****************************************************************************
 *  vcardupdatefactory.cpp
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

#include "vcardupdatefactory_p.h"
#include <QXmlStreamWriter>
#include <QStringList>
#define NS_VCARDUPDATE QLatin1String("vcard-temp:x:update")

namespace jreen
{

VCardUpdateFactory::VCardUpdateFactory()
{
	m_hasPhoto = false;
	m_depth = 0;
	m_isPhoto = false;
}

VCardUpdateFactory::~VCardUpdateFactory()
{

}

QStringList VCardUpdateFactory::features() const
{
	return QStringList(NS_VCARDUPDATE);
}

bool VCardUpdateFactory::canParse(const QStringRef &name, const QStringRef &uri,
								  const QXmlStreamAttributes &attributes)
{
	Q_UNUSED(attributes);
	return name == QLatin1String("x") && uri == NS_VCARDUPDATE;
}

void VCardUpdateFactory::handleStartElement(const QStringRef &name,
											const QStringRef &uri, const QXmlStreamAttributes &attributes)
{
	Q_UNUSED(uri);
	Q_UNUSED(attributes);
	m_depth++;
	if (m_depth == 1) {
		m_hasPhoto = false;
		m_hash.clear();
	} else if(m_depth == 2) {
		m_isPhoto = name == QLatin1String("photo");
		m_hasPhoto |= m_isPhoto;
	}
}

void VCardUpdateFactory::handleEndElement(const QStringRef &name, const QStringRef &uri)
{
	Q_UNUSED(name);
	Q_UNUSED(uri);
	if (m_depth == 2)
		m_isPhoto = false;
	m_depth--;
}

void VCardUpdateFactory::handleCharacterData(const QStringRef &text)
{
	if(m_depth == 2 && m_isPhoto)
		m_hash = text.toString();
}

void VCardUpdateFactory::serialize(StanzaExtension *extension, QXmlStreamWriter *writer)
{
	VCardUpdate *update = se_cast<VCardUpdate*>(extension);
	writer->writeStartElement(QLatin1String("x"));
	writer->writeDefaultNamespace(NS_VCARDUPDATE);
	writer->writeTextElement(QLatin1String("photo"),update->photoHash());
	writer->writeEndElement();
}

StanzaExtension::Ptr VCardUpdateFactory::createExtension()
{
	VCardUpdate *update = new VCardUpdate;
	if (m_hasPhoto)
		update->setPhotoHash(m_hash);
	return StanzaExtension::Ptr(update);
}

} // namespace jreen
