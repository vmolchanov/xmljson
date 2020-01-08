#ifndef FILE_H
#define FILE_H

#include <QApplication>

class IFile {
public:
    virtual void parse(const QByteArray text) = 0;

    virtual QByteArray translate() = 0;
};

#endif
