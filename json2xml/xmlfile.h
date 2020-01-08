#ifndef XMLFILE_H
#define XMLFILE_H

#include <QApplication>
#include <QtXml>
#include "file.h"
#include "xml2json.h"

class XmlFile : public File
{
public:
    XmlFile();

    void parse(const QByteArray text);

    QByteArray translate();

private:
    char const *_data;
};

#endif
