cmake_minimum_required(VERSION 3.27)
project(BinaryFileModifier)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#cmake path for Qt
set(CMAKE_PREFIX_PATH "C:/Qt/6.4.2/mingw_64/lib/cmake")


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(BinaryFileModifier main.cpp
        Widgets/MainWindow/mainwindow.cpp
        Widgets/MainWindow/mainwindow.h
        Widgets/MainWindow/mainwindow.ui
        model/ModificationSettings/ModificationSettings.h
        model/ModificationSettings/ModificationSettings.cpp
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
        src/Logger/ThreadSafeLogger/ThreadSafeLogger.h)
target_link_libraries(BinaryFileModifier
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()