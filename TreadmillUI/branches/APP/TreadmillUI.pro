######################################################################
# Automatically generated by qmake (2.01a) Wed Sep 29 17:43:36 2010
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += startupwindow.h \
    mainscreen.h \
    historywidget.h \
    heartratescreen.h \
    sliderwidget.h \
    fitnesstestscreen.h \
    weightsliderwidget.h \
    agesliderwidget.h \
    timesliderwidget.h \
    fatburnscreen.h \
    preferences.h \
    intervalscreen.h \
    speedsliderwidget.h \
    gradesliderwidget.h \
    abstractscreen.h \
    abstractmultisliderscreen.h \
    pointerevent.h \
    testwidget.h \
    audiosettingswidget.h \
    radiosliderwidget.h \
    keyboardwidget.h \
    myworkoutsscreen.h \
    newworkoutscreen.h \
    invisiblebutton.h \
    screens.h \
    seriallistenerthread.h \
    serialsenderthread.h \
    upperboardevent.h \
    utils.h \
    state.h \
    changespeedstep.h \
    changegradestep.h \
    waitstep.h \
    step.h
FORMS += startupwindow.ui \
    mainscreen.ui \
    heartratescreen.ui \
    fitnesstestscreen.ui \
    fatburnscreen.ui \
    intervalscreen.ui \
    audiosettingswidget.ui \
    keyboardwidget.ui \
    myworkoutsscreen.ui \
    newworkoutscreen.ui
SOURCES += main.cpp startupwindow.cpp \
    mainscreen.cpp \
    historywidget.cpp \
    heartratescreen.cpp \
    sliderwidget.cpp \
    fitnesstestscreen.cpp \
    weightsliderwidget.cpp \
    agesliderwidget.cpp \
    timesliderwidget.cpp \
    fatburnscreen.cpp \
    preferences.cpp \
    intervalscreen.cpp \
    speedsliderwidget.cpp \
    gradesliderwidget.cpp \
    abstractscreen.cpp \
    abstractmultisliderscreen.cpp \
    pointerevent.cpp \
    testwidget.cpp \
    audiosettingswidget.cpp \
    radiosliderwidget.cpp \
    keyboardwidget.cpp \
    myworkoutsscreen.cpp \
    newworkoutscreen.cpp \
    invisiblebutton.cpp \
    screens.cpp \
    seriallistenerthread.cpp \
    serialsenderthread.cpp \
    upperboardevent.cpp \
    utils.cpp \
    state.cpp \
    changespeedstep.cpp \
    changegradestep.cpp \
    waitstep.cpp \
    step.cpp
RESOURCES += images.qrc

OTHER_FILES += \
    style.css

#QT += phonon
LIBS += -lqextserialport
#DEFINES += QT_NO_DEBUG_OUTPUT NDEBUG
