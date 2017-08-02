
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtCTP
TEMPLATE = app
DEFINES += MD_API_EXPORT

HEADERS += \
    dduictpwidget.h \
    dduimarketdataapi.h \
    dduitraderapi.h \
    dduictpconfig.h \
    dduifutrueview.h

SOURCES += \
    dduictpwidget.cpp \
    main.cpp \
    dduimarketdataapi.cpp \
    dduitraderapi.cpp \
    dduifutrueview.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/tradeapidll/32/ -lthostmduserapi
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/tradeapidll/32/ -lthostmduserapi

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/tradeapidll/32/ -lthosttraderapi
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/tradeapidll/32/ -lthosttraderapi

INCLUDEPATH += $$PWD/tradeapidll/32
DEPENDPATH += $$PWD/tradeapidll/32

#copy those dll to run path
libfile.files += $$PWD/tradeapidll/32/*.dll
win32:CONFIG(release, debug|release):libfile.path = $$PWD/release
else:win32:CONFIG(debug, debug|release):libfile.path  = $$PWD/debug

FORMS += \
    dduifutrueview.ui

