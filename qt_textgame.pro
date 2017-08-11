QT += qml quick

CONFIG += c++11

SOURCES += \
    src/main.cpp \
    src/parser.cpp \
    src/scene.cpp \
    src/textgame.cpp \
    src/textgamecontroller.cpp \
    src/qtparser.cpp \
    src/mktohtml/mk.cpp \
    src/mktohtml/mktohtml.cpp \
    src/mktohtml/newmk.cpp

HEADERS += \
    src/global.h \
    src/parser.hpp \
    src/scene.h \
    src/textgame.h \
    src/textgamecontroller.h \
    src/qtparser.h \
    src/mktohtml/mk.h \

RESOURCES += \
    src/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#DISTFILES += \
#    src/qml/main.qml \
#    src/qml/StartMenu.qml \
#    src/qml/TextApp.qml
