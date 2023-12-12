cmake_minimum_required(VERSION 3.26)
project(Centsible)

set(CMAKE_CXX_STANDARD 17)

# QT6
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Charts)

#if (APPLE)
#    message("CMAKE found OSX system. If this is not correct please abort!")
#    set(CMAKE_PREFIX_PATH "/usr/local/cellar/qt/6.6.0")
#elseif (CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
#    message("CMAKE found windows system. If this is not correct please abort!")
#    set(CMAKE_PREFIX_PATH "C:/Qt/6.6.1/mingw_64/bin")
#endif ()

add_executable(Centsible main.cpp
        mainwindow.cpp mainwindow.h
        mongoloid.cpp mongoloid.h)

target_link_libraries(Centsible PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts)

# Copy resources to build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/mongo DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

