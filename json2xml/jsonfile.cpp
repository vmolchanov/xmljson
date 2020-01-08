#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QXmlStreamWriter>
#include <QtMath>
#include "jsonfile.h"

JsonFile::JsonFile() : File() {
}

void JsonFile::parse(const QByteArray text) {
    _data = QJsonDocument::fromJson(text);
}

QByteArray JsonFile::translate() {
    const QString ROOT_TAG_NAME = "root";
    QByteArray xml;

    if (_data.isEmpty() || _data.isNull()) {
        return xml;
    }

    QXmlStreamWriter xmlStreamWriter(&xml);

    xmlStreamWriter.setAutoFormatting(true);
    xmlStreamWriter.writeStartDocument();

    if (_data.isArray()) {
        _arrayToXml(_data.array(), ROOT_TAG_NAME, xmlStreamWriter);
    } else if (_data.isObject()) {
        _objectToXml(_data.object(), ROOT_TAG_NAME, xmlStreamWriter);
    }

    return xml;
}

int JsonFile::_guessPrecision(double value) {
    double junk;
    int precision;

    for (precision = 0; !qFuzzyIsNull(std::modf(value, &junk)); precision++) {
        value *= 10.0;
    }

    return precision;
}

void JsonFile::_valueToXml(const QJsonValue& value, const QString& tagName, QXmlStreamWriter& xmlStreamWriter) {
    if (value.isNull() || value.isUndefined()) {
        return;
    }

    if (value.isObject()) {
        return _objectToXml(value.toObject(), tagName, xmlStreamWriter);
    }

    if (value.isArray()) {
        return _arrayToXml(value.toArray(), tagName, xmlStreamWriter);
    }

    xmlStreamWriter.writeStartElement(tagName);

    if (value.isBool()) {
        const QString boolValue = value.toBool() ? QStringLiteral("true") : QStringLiteral("false");
        xmlStreamWriter.writeCharacters(boolValue);
    } else if (value.isDouble()) {
        const double doubleValue = value.toDouble();
        xmlStreamWriter.writeCharacters(QString::number(doubleValue, 'f', _guessPrecision(doubleValue)));
    } else {
        xmlStreamWriter.writeCharacters(value.toString());
    }

    xmlStreamWriter.writeEndElement();
}

void JsonFile::_objectToXml(const QJsonObject& object, const QString& tagName, QXmlStreamWriter& xmlStreamWriter) {
    if (object.isEmpty()) {
        return;
    }

    xmlStreamWriter.writeStartElement(tagName);

    for (auto i = object.constBegin(), objEnd = object.constEnd(); i != objEnd; i++) {
        _valueToXml(*i, i.key(), xmlStreamWriter);
    }

    xmlStreamWriter.writeEndElement();
}

void JsonFile::_arrayToXml(const QJsonArray& array, const QString& tagName, QXmlStreamWriter& xmlStreamWriter) {
    xmlStreamWriter.writeStartElement(tagName);

    for (int i = 0; i < array.size(); i++) {
        _valueToXml(array.at(i), tagName + QString::number(i), xmlStreamWriter);
    }

    xmlStreamWriter.writeEndElement();
}
