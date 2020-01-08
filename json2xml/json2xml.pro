QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


QMAKE_LFLAGS += -v


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    file.cpp \
    filefactory.cpp \
    jsonfile.cpp \
    main.cpp \
    mainwindow.cpp \
    xml2json.cpp \
    xmlfile.cpp

HEADERS += \
    file.h \
    filefactory.h \
    jsonfile.h \
    mainwindow.h \
    rapidjson/allocators.h \
    rapidjson/allocators.h \
    rapidjson/document.h \
    rapidjson/document.h \
    rapidjson/document.h \
    rapidjson/encodedstream.h \
    rapidjson/encodedstream.h \
    rapidjson/encodedstream.h \
    rapidjson/encodings.h \
    rapidjson/encodings.h \
    rapidjson/error/en.h \
    rapidjson/error/en.h \
    rapidjson/error/en.h \
    rapidjson/error/error.h \
    rapidjson/error/error.h \
    rapidjson/filereadstream.h \
    rapidjson/filereadstream.h \
    rapidjson/filereadstream.h \
    rapidjson/filewritestream.h \
    rapidjson/filewritestream.h \
    rapidjson/filewritestream.h \
    rapidjson/fwd.h \
    rapidjson/fwd.h \
    rapidjson/internal/biginteger.h \
    rapidjson/internal/biginteger.h \
    rapidjson/internal/diyfp.h \
    rapidjson/internal/diyfp.h \
    rapidjson/internal/dtoa.h \
    rapidjson/internal/dtoa.h \
    rapidjson/internal/ieee754.h \
    rapidjson/internal/ieee754.h \
    rapidjson/internal/itoa.h \
    rapidjson/internal/itoa.h \
    rapidjson/internal/meta.h \
    rapidjson/internal/meta.h \
    rapidjson/internal/pow10.h \
    rapidjson/internal/pow10.h \
    rapidjson/internal/regex.h \
    rapidjson/internal/regex.h \
    rapidjson/internal/stack.h \
    rapidjson/internal/stack.h \
    rapidjson/internal/strfunc.h \
    rapidjson/internal/strfunc.h \
    rapidjson/internal/strtod.h \
    rapidjson/internal/strtod.h \
    rapidjson/internal/swap.h \
    rapidjson/internal/swap.h \
    rapidjson/istreamwrapper.h \
    rapidjson/istreamwrapper.h \
    rapidjson/memorybuffer.h \
    rapidjson/memorybuffer.h \
    rapidjson/memorystream.h \
    rapidjson/memorystream.h \
    rapidjson/msinttypes/inttypes.h \
    rapidjson/msinttypes/inttypes.h \
    rapidjson/msinttypes/stdint.h \
    rapidjson/msinttypes/stdint.h \
    rapidjson/ostreamwrapper.h \
    rapidjson/ostreamwrapper.h \
    rapidjson/pointer.h \
    rapidjson/pointer.h \
    rapidjson/prettywriter.h \
    rapidjson/prettywriter.h \
    rapidjson/prettywriter.h \
    rapidjson/rapidjson.h \
    rapidjson/rapidjson.h \
    rapidjson/reader.h \
    rapidjson/reader.h \
    rapidjson/reader.h \
    rapidjson/schema.h \
    rapidjson/schema.h \
    rapidjson/stream.h \
    rapidjson/stream.h \
    rapidjson/stringbuffer.h \
    rapidjson/stringbuffer.h \
    rapidjson/stringbuffer.h \
    rapidjson/writer.h \
    rapidjson/writer.h \
    rapidjson/writer.h \
    rapidxml/rapidxml.hpp \
    rapidxml/rapidxml.hpp \
    rapidxml/rapidxml.hpp \
    rapidxml/rapidxml_iterators.hpp \
    rapidxml/rapidxml_iterators.hpp \
    rapidxml/rapidxml_print.hpp \
    rapidxml/rapidxml_print.hpp \
    rapidxml/rapidxml_print.hpp \
    rapidxml/rapidxml_utils.hpp \
    rapidxml/rapidxml_utils.hpp \
    rapidxml/rapidxml_utils.hpp \
    xml2json.h \
    xml2json.h \
    xmlfile.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    rapidxml/license.txt \
    rapidxml/manual.html
