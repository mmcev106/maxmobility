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
    abstractkeyboardwidget.h \
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
    messagescreen.h \
    tranquilselectionwidget.h \
    trailselectionwidget.h \
    scorewidget.h \
    endstep.h \
    webview.h \
    keyboardscreen.h \
    largekeyboardwidget.h \
    smallkeyboardwidget.h \
    serialreconnectthread.h \
    ../TreadmillUI-build-desktop/ui_videoscreen.h \
    ../TreadmillUI-build-desktop/ui_usbwarningscreen.h \
    ../TreadmillUI-build-desktop/ui_tranquilselectionwidget.h \
    ../TreadmillUI-build-desktop/ui_trailselectionwidget.h \
    ../TreadmillUI-build-desktop/ui_startupwindow.h \
    ../TreadmillUI-build-desktop/ui_smallkeyboardwidget.h \
    ../TreadmillUI-build-desktop/ui_settingsscreen.h \
    ../TreadmillUI-build-desktop/ui_scorewidget.h \
    ../TreadmillUI-build-desktop/ui_outdoorpathsscreen.h \
    ../TreadmillUI-build-desktop/ui_newworkoutscreen.h \
    ../TreadmillUI-build-desktop/ui_myworkoutsscreen.h \
    ../TreadmillUI-build-desktop/ui_messagescreen.h \
    ../TreadmillUI-build-desktop/ui_mainscreen.h \
    ../TreadmillUI-build-desktop/ui_largekeyboardwidget.h \
    ../TreadmillUI-build-desktop/ui_keyboardscreen.h \
    ../TreadmillUI-build-desktop/ui_intervalscreen.h \
    ../TreadmillUI-build-desktop/ui_historyscreen.h \
    ../TreadmillUI-build-desktop/ui_heartratescreen.h \
    ../TreadmillUI-build-desktop/ui_fitnesstestscreen.h \
    ../TreadmillUI-build-desktop/ui_fatburnscreen.h \
    ../TreadmillUI-build-desktop/ui_calibrationscreen.h \
    ../TreadmillUI-build-desktop/ui_audiosettingswidget.h
FORMS += startupwindow.ui \
    mainscreen.ui \
    heartratescreen.ui \
    fitnesstestscreen.ui \
    fatburnscreen.ui \
    intervalscreen.ui \
    audiosettingswidget.ui \
    smallkeyboardwidget.ui \
    myworkoutsscreen.ui \
    newworkoutscreen.ui \
    historyscreen.ui \
    videoscreen.ui \
    usbwarningscreen.ui \
    outdoorpathsscreen.ui \
    settingsscreen.ui \
    calibrationscreen.ui \
    messagescreen.ui \
    tranquilselectionwidget.ui \
    trailselectionwidget.ui \
    scorewidget.ui \
    keyboardscreen.ui \
    largekeyboardwidget.ui
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
    abstractkeyboardwidget.cpp \
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
    messagescreen.cpp \
    tranquilselectionwidget.cpp \
    trailselectionwidget.cpp \
    scorewidget.cpp \
    endstep.cpp \
    webview.cpp \
    keyboardscreen.cpp \
    largekeyboardwidget.cpp \
    smallkeyboardwidget.cpp \
    serialreconnectthread.cpp
RESOURCES += images.qrc \
    jquery.qrc

OTHER_FILES += \
    style.css \
    images/Outdoor Paths - Wooded Path.png \
    images/Outdoor Paths - Wooded Path.png

CONFIG += warn_off

QT += phonon
QT += opengl
QT += webkit network multimedia
QT += testlib #for displaying a console on release builds
LIBS += -lqextserialport
#DEFINES += QT_NO_DEBUG_OUTPUT NDEBUG
