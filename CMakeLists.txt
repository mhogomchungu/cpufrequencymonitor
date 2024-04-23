cmake_minimum_required(VERSION 3.5)

project(CPUFrequencyMonitor VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

INCLUDE(GNUInstallDirs)

set(RESOURCES src/icon.qrc )

set(PROJECT_SOURCES
        src/main.cpp
        src/cpu.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(cpufrequencymonitor MANUAL_FINALIZATION ${PROJECT_SOURCES})
else()
    add_executable(cpufrequencymonitor ${PROJECT_SOURCES} ${RESOURCES})
endif()

target_link_libraries(cpufrequencymonitor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(cpufrequencymonitor PROPERTIES COMPILE_FLAGS "-Wextra -Wall -s -pedantic")

# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

install(TARGETS cpufrequencymonitor RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES src/cpufrequencymonitor.desktop DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications)
install(FILES src/cpufrequencymonitor.png DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pixmaps)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(cpufrequencymonitor)
endif()
