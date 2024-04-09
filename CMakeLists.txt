cmake_minimum_required(VERSION 3.5)

project(BinaryFileModifier VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        Widgets/MainWindow/mainwindow.cpp
        Widgets/MainWindow/mainwindow.h
        Widgets/MainWindow/mainwindow.ui
        model/ModificationSettings/ModificationSettings.h
        model/ModificationSettings/ModificationSettings.cpp
        test/test.cpp
        src/SettingsObserver/SettingsObserver.cpp
        src/SettingsObserver/SettingsObserver.h
        src/config/AppConfig/AppConfig.cpp
        src/config/AppConfig/AppConfig.h
        src/Logger/LoggerInterface.h
        src/Logger/TextBrowserLogger/TextBrowserLogger.cpp
        src/Logger/TextBrowserLogger/TextBrowserLogger.h
        src/Logger/TextStreamLogger/TextStreamLogger.cpp
        src/Logger/TextStreamLogger/TextStreamLogger.h
        src/FileModifier/FileModifier.cpp
        src/FileModifier/FileModifier.h
        src/Logger/ThreadSafeLogger/ThreadSafeLogger.cpp
        src/Logger/ThreadSafeLogger/ThreadSafeLogger.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BinaryFileModifier
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
    )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET BinaryFileModifier APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(BinaryFileModifier SHARED
                ${PROJECT_SOURCES}
        )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(BinaryFileModifier
                ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(BinaryFileModifier PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(BinaryFileModifier PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

install(TARGETS BinaryFileModifier
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BinaryFileModifier)
endif()
