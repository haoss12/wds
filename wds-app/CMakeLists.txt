cmake_minimum_required(VERSION 3.5)

project(wds-app VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets OpenGL LinguistTools SerialPort Charts REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets OpenGL LinguistTools SerialPort Charts REQUIRED)
# find_package(Qt5::SerialPort)

set(TS_FILES wds-app_en_EN.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        dataframe.h
        dataframe.cpp
        crc8.h
        crc8.cpp
        rocketrenderer.h
        rocketrenderer.cpp
        mainwindow.ui
        ${TS_FILES}

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(wds-app
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${QM_FILES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET wds-app APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} wds-app_en_EN.ts)

else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} wds-app_en_EN.ts)
    if(ANDROID)
        add_library(wds-app SHARED
            ${PROJECT_SOURCES}
            ${QM_FILES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(wds-app
            ${PROJECT_SOURCES}
            ${QM_FILES}
        )
    endif()

endif()

target_link_libraries(wds-app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt5::SerialPort Qt5::OpenGL Qt5::Charts ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

set_target_properties(wds-app PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(wds-app)
endif()
