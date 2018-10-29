TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/sources/main.cpp \
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
    src/headers/displaymanager.h \
    src/headers/inputhandler.h \
    src/headers/renderingunit.h \
    src/headers/masterheader.h \
    src/headers/shader.h \
    src/headers/texture.h \
    src/headers/errorhandler.h \
    src/headers/model.h \
    src/headers/glmath.h \
    src/headers/camera.h \
    src/headers/entity.h

unix|win32: LIBS += -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

INCLUDEPATH +=  include \

include(include/include.pri)
include(shaders/shaders.pri)
