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
    step.h \
    historyscreen.h \
    workout.h \
    historyitem.h \
    videoscreen.h \
    usbwarningscreen.h \
    outdoorpathsscreen.h \
    intensitysliderwidget.h \
    videoplayer.h \
    WebWidget.h \
    useragentwebpage.h \
    settingsscreen.h \
    calibrationscreen.h \
    resultsscreen.h \
    tranquilselectionwidget.h \
    trailselectionwidget.h
FORMS += startupwindow.ui \
    mainscreen.ui \
    heartratescreen.ui \
    fitnesstestscreen.ui \
    fatburnscreen.ui \
    intervalscreen.ui \
    audiosettingswidget.ui \
    keyboardwidget.ui \
    myworkoutsscreen.ui \
    newworkoutscreen.ui \
    historyscreen.ui \
    videoscreen.ui \
    usbwarningscreen.ui \
    outdoorpathsscreen.ui \
    settingsscreen.ui \
    calibrationscreen.ui \
    resultsscreen.ui \
    tranquilselectionwidget.ui \
    trailselectionwidget.ui
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
    step.cpp \
    historyscreen.cpp \
    workout.cpp \
    historyitem.cpp \
    videoscreen.cpp \
    usbwarningscreen.cpp \
    outdoorpathsscreen.cpp \
    intensitysliderwidget.cpp \
    videoplayer.cpp \
    WebWidget.cpp \
    useragentwebpage.cpp \
    settingsscreen.cpp \
    calibrationscreen.cpp \
    resultsscreen.cpp \
    tranquilselectionwidget.cpp \
    trailselectionwidget.cpp
RESOURCES += images.qrc \
    jquery.qrc

OTHER_FILES += \
    style.css \
    images/Outdoor Paths - Wooded Path.png \
    images/Outdoor Paths - Wooded Path.png

CONFIG += warn_off

QT += phonon
QT += opengl
QT += webkit network
LIBS += -lqextserialport
#DEFINES += QT_NO_DEBUG_OUTPUT NDEBUG
