cmake_minimum_required(VERSION 3.26)
project(Centsible)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "/usr/local/cellar/qt/6.6.0")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
  Core
  Gui
  Widgets
  REQUIRED)

add_executable(Centsible main.cpp
        mainwindow.cpp
        mainwindow.h)
target_link_libraries(Centsible
  Qt6::Core
  Qt6::Gui
  Qt6::Widgets
)

