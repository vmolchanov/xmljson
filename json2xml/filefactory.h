#ifndef FILEFACTORY_H
#define FILEFACTORY_H

#include "ifile.h"

class FileFactory {
public:
    IFile* createFileByFlag(bool isJson);
};

#endif
