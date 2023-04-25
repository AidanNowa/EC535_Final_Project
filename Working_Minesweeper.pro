QT += widgets
requires(qtConfig(combobox))

HEADERS       = mybutton.h 
SOURCES       = main.cpp \
                mybutton.cpp
RESOURCES     = minesweeper.qrc

# install
target.path = /home/aidannow/EC535/lab5/Working_Minesweeper
INSTALLS += target
