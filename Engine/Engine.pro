QT       -= core gui

TARGET = Engine
TEMPLATE = lib

SOURCES += \
    src/sources/displaymanager.cpp \
    src/sources/inputhandler.cpp \
    src/sources/renderingunit.cpp \
    src/sources/shader.cpp \
    src/sources/texture.cpp \
    src/sources/stb_image.cpp \
    src/sources/model.cpp \
    src/sources/glmath.cpp \
    src/sources/camera.cpp \
    src/sources/entity.cpp

HEADERS += \
    src/headers/*.h

INCLUDEPATH +=  include \
    src/headers \

include(include/include.pri)

unix {
    target.path = /usr/lib
    INSTALLS += target
}

