QT += quick

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        alphaomega.cpp \
        consumer.cpp \
        doublepipe.cpp \
        gameobject.cpp \
        level.cpp \
        main.cpp \
        pipe.cpp \
        solver.cpp \
        source.cpp \
        tap.cpp \
        tester.cpp \
        tinyxml/tinyxml2.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    alphaomega.h \
    consumer.h \
    doublepipe.h \
    gameobject.h \
    level.h \
    pipe.h \
    solver.h \
    source.h \
    tap.h \
    tester.h \
    tinyxml/tinyxml2.h
