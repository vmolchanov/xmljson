#include "filefactory.h"
#include "jsonfile.h"
#include "xmlfile.h"

IFile* FileFactory::createFileByFlag(bool isJson) {
    if (isJson) {
        return new JsonFile();
    } else {
        return new XmlFile();
    }
}
