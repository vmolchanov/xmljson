#include "filefactory.h"
#include "jsonfile.h"
#include "xmlfile.h"

File* FileFactory::createFileByFlag(bool isJson) {
    if (isJson) {
        return new JsonFile();
    } else {
        return new XmlFile();
    }
}
