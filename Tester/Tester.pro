TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
	src/sources/Application.cpp

INCLUDEPATH += \
        $$PWD/../Engine/src/headers \
        $$PWD/../Engine/include \
        src/headers/

HEADERS += \
        engine.h

unix|win32: LIBS += -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

LIBS += \
    -L$$OUT_PWD/../Engine/ -lEngine

OTHER_FILES += \
    shader/shaders.pri \
    res/*

include(shaders/shaders.pri)


