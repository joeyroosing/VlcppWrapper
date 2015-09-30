TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11
CONFIG -= qt
HEADERS = vlcinstance.h \
    vlcerror.h \
    vlccommon.h \
    vlcstats.h \
    vlcvideoframe.h \
    vlcmedia.h \
    vlcenums.h \
    sizef.h
SOURCES = vlcinstance.cpp \
    vlcerror.cpp \
    vlccommon.cpp \
    vlcvideoframe.cpp \
    vlcmedia.cpp \
    vlcenums.cpp \
    sizef.cpp

LIBS += -llibvlc
LIBS += -llibvlccore

LIBS += -LC:\vlc-2.2.1\VLC
INCLUDEPATH += C:\vlc-2.2.1\VLC\sdk\include
