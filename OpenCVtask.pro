QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    imagethread.cpp \
    lane.cpp \
    main.cpp \
    dialog.cpp

HEADERS += \
    dialog.h \
    imagethread.h \
    lane.h

FORMS += \
    dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -LC:/opencv_build/install/x64/vc15/lib/ -lopencv_imgproc450
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/opencv_build/install/x64/vc15/lib/ -lopencv_imgproc450d
else:unix: LIBS += -LC:/opencv_build/install/x64/vc15/lib/ -lopencv_imgproc450

INCLUDEPATH += C:/opencv_build/install/include
DEPENDPATH += C:/opencv_build/install/include





win32:CONFIG(release, debug|release): LIBS += -LC:/opencv_build/install/x64/vc15/lib/ -lopencv_videoio450
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/opencv_build/install/x64/vc15/lib/ -lopencv_videoio450d
else:unix: LIBS += -LC:/opencv_build/install/x64/vc15/lib/ -lopencv_videoio450



win32:CONFIG(release, debug|release): LIBS += -LC:/opencv_build/install/x64/vc15/lib/ -lopencv_video450
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/opencv_build/install/x64/vc15/lib/ -lopencv_video450d
else:unix: LIBS += -LC:/opencv_build/install/x64/vc15/lib/ -lopencv_video450

win32:CONFIG(release, debug|release): LIBS += -LC:/opencv_build/install/x64/vc15/lib/ -lopencv_core450d
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/opencv_build/install/x64/vc15/lib/ -lopencv_core450d
else:unix: LIBS += -LC:/opencv_build/install/x64/vc15/lib/ -lopencv_core450d

INCLUDEPATH += C:/opencv_build/install/include
DEPENDPATH += C:/opencv_build/install/include

win32:CONFIG(release, debug|release): LIBS += -LC:/opencv_build/install/x64/vc15/lib/ -lopencv_highgui450d
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/opencv_build/install/x64/vc15/lib/ -lopencv_highgui450d
else:unix: LIBS += -LC:/opencv_build/install/x64/vc15/lib/ -lopencv_highgui450d

INCLUDEPATH += C:/opencv_build/install/include
DEPENDPATH += C:/opencv_build/install/include

win32:CONFIG(release, debug|release): LIBS += -LC:/opencv_build/install/x64/vc15/lib/ -lopencv_imgcodecs450d
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/opencv_build/install/x64/vc15/lib/ -lopencv_imgcodecs450d
else:unix: LIBS += -LC:/opencv_build/install/x64/vc15/lib/ -lopencv_imgcodecs450d

INCLUDEPATH += C:/opencv_build/install/include
DEPENDPATH += C:/opencv_build/install/include
