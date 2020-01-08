#ifndef XMLFILE_H
#define XMLFILE_H

#include <QApplication>
#include <QtXml>
#include "ifile.h"
#include "xml2json.h"

class XmlFile : public IFile {
public:
    XmlFile();

    void parse(const QByteArray text);

    QByteArray translate();

private:
    char const *_data;
};

#endif
