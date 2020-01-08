#ifndef JSONFILE_H
#define JSONFILE_H

#include <QApplication>
#include <QJsonDocument>
#include <QXmlStreamWriter>
#include "file.h"

class JsonFile : public File
{
public:
    JsonFile();
    void parse(const QByteArray text);

    QByteArray translate();

private:
    QJsonDocument _data;

    static int _guessPrecision(double val);

    static void _valueToXml(const QJsonValue& val, const QString& name, QXmlStreamWriter& writer);

    static void _objectToXml(const QJsonObject& obj, const QString& name, QXmlStreamWriter& writer);

    static void _arrayToXml(const QJsonArray& arr, const QString& name, QXmlStreamWriter& writer);
};

#endif
