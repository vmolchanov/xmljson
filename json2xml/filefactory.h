#ifndef FILEFACTORY_H
#define FILEFACTORY_H

#include "file.h"

class FileFactory {
public:
    File* createFileByFlag(bool isJson);
};

#endif
