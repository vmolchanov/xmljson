#include <QXmlStreamReader>
#include <QtDebug>
#include <string>
#include <QtXml>
#include <QJsonDocument>
#include "xmlfile.h"

XmlFile::XmlFile() : IFile() {
}

void XmlFile::parse(const QByteArray text) {
    _data = text.toStdString().c_str();
}

QByteArray XmlFile::translate() {
    const std::string json = xml2json(_data);

    // Для форматированного вывода
    QJsonDocument document = QJsonDocument::fromJson(QByteArray(json.data()));
    QString formattedJson = document.toJson(QJsonDocument::Indented);

    return QByteArray(formattedJson.toStdString().c_str());
}
