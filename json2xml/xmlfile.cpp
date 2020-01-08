#include <QXmlStreamReader>
#include <QtDebug>
#include <string>
#include <QtXml>
#include "xmlfile.h"
//#include "xml2json.h"

XmlFile::XmlFile() : File() {
}

void XmlFile::parse(const QByteArray text) {
    _data = text.toStdString().c_str();
}

QByteArray XmlFile::translate() {
    const std::string json_str = xml2json(_data);
    return QByteArray(json_str.data());
}
