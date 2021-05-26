QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
#CONFIG += console       // For Console Output

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    LXML/FileIO.cpp \
    LXML/LXML.cpp \
    LXML/LXMLConnector.cpp \
    LXML/LXMLElement.cpp \
    LXML/LXMLRegMatcher.cpp \
    LXML/LXMLTagAnalyser.cpp \
    LXMLObjectMapper/LXMLObject.cpp \
    MultimapKeyedTree/MultimapKeyedTree.cpp \
    MultimapKeyedTree/MultimapKeyedTreeConnector.cpp \
    MultimapKeyedTree/MultimapKeyedTreeElement.cpp \
    controls/blackcircle.cpp \
    controls/board.cpp \
    controls/chooser.cpp \
    controls/dots.cpp \
    controls/muggui.cpp \
    controls/muglist.cpp \
    controls/reddot.cpp \
    gamelogic/Confi.cpp \
    gamelogic/Controller.cpp \
    gamelogic/GUI.cpp \
    gamelogic/GUIStart.cpp \
    gamelogic/Game.cpp \
    gamelogic/Move.cpp \
    gamelogic/Mug.cpp \
    gamelogic/Mugmap.cpp \
    gamelogic/Observer.cpp \
    gamelogic/Player.cpp \
    gamelogic/PlayerAI.cpp \
    gamelogic/PlayerHuman.cpp \
    gamelogic/PlayerPool.cpp \
    gamelogic/PlayerRandom.cpp \
    gamelogic/Playground.cpp \
    gamelogic/Session.cpp \
    gamelogic/Start.cpp \
    gamelogic/guiplaygroundbase.cpp \
    info.cpp \
    gamethread.cpp \
    gui_qt.cpp \
    main.cpp \
    mainwindow.cpp \
    matrix.cpp

HEADERS += \
    LXML/FileIO.h \
    LXML/LXML.h \
    LXML/LXMLConnector.h \
    LXML/LXMLConsts.h \
    LXML/LXMLElement.h \
    LXML/LXMLFunctions.h \
    LXML/LXMLRegMatcher.h \
    LXML/LXMLRegMatcher_TestOutlet.h \
    LXML/LXMLTagAnalyser.h \
    LXML/LXMLTagAnalyser_TestOutlet.h \
    LXML/LXMLTypes.h \
    LXMLObjectMapper/LXMLObject.h \
    LXMLObjectMapper/LXMLObject_Consts.h \
    MultimapKeyedTree/MultimapKeyedTree.h \
    MultimapKeyedTree/MultimapKeyedTreeConnector.h \
    MultimapKeyedTree/MultimapKeyedTreeElement.h \
    controls/blackcircle.h \
    controls/board.h \
    controls/chooser.h \
    controls/dots.h \
    controls/muggui.h \
    controls/muglist.h \
    controls/reddot.h \
    gamelogic/Confi.h \
    gamelogic/Controller.h \
    gamelogic/Controller_structs.h \
    gamelogic/GUI.h \
    gamelogic/GUIStart.h \
    gamelogic/Game.h \
    gamelogic/Move.h \
    gamelogic/Mug.h \
    gamelogic/Mugmap.h \
    gamelogic/Observer.h \
    gamelogic/Player.h \
    gamelogic/PlayerAI.h \
    gamelogic/PlayerHuman.h \
    gamelogic/PlayerPool.h \
    gamelogic/PlayerRandom.h \
    gamelogic/Playground.h \
    gamelogic/Session.h \
    gamelogic/Start.h \
    gamelogic/global_classes.h \
    gamelogic/global_const.h \
    gamelogic/global_exception.h \
    gamelogic/global_flags.h \
    gamelogic/global_func.h \
    gamelogic/global_macros.h \
    gamelogic/global_typedef.h \
    gamelogic/globals_globals.h \
    gamelogic/guiplaygroundbase.h \
    gamelogic/template_Cycle.h \
    gamethread.h \
    gui_qt.h \
    info.h \
    mainwindow.h \
    matrix.h

FORMS += \
    info.ui \
    mainwindow.ui \
    matrix.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
