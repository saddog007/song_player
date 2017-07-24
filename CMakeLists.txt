cmake_minimum_required (VERSION 2.8 FATAL_ERROR)

project      (songPlayer)
find_package (Qt5 COMPONENTS Widgets SerialPort Multimedia xml Network)

set (SONGPLAYER_ROOT ${CMAKE_SOURCE_DIR}/..)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set  (DEMO_SRC
    ${SONGPLAYER_ROOT}/src/ui_backpic.h
    ${SONGPLAYER_ROOT}/src/ui_mainwindow.h
    ${SONGPLAYER_ROOT}/src/backpic.h
    ${SONGPLAYER_ROOT}/src/mainwindow.h
    ${SONGPLAYER_ROOT}/src/mymaintable.h

    ${SONGPLAYER_ROOT}/src/main.cpp
    ${SONGPLAYER_ROOT}/src/backpic.cpp
    ${SONGPLAYER_ROOT}/src/mainwindow.cpp
    ${SONGPLAYER_ROOT}/src/mymaintable.cpp
)


QT5_ADD_RESOURCES (PROJECT_RESOURCES song_image.qrc)


ADD_EXECUTABLE  (SongPlayer_Saddog ${DEMO_SRC} ${PROJECT_RESOURCES})

TARGET_LINK_LIBRARIES (SongPlayer_Saddog Qt5::Core Qt5::SerialPort Qt5::Widgets Qt5::Gui  Qt5::Multimedia Qt5::Network )

