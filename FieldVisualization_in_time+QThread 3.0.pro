HEADERS       = glwidget.h \
                window.h \
                logo.h \
                field.h \
                settingswindow.h

SOURCES       = glwidget.cpp \
                main.cpp \
                window.cpp \
                logo.cpp \
                field.cpp \
                settingswindow.cpp

QT           += widgets

## install
#target.path = $$[QT_INSTALL_EXAMPLES]/opengl/hellogl2
#INSTALLS += target

FORMS += \
                settingswindow.ui
