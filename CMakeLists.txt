cmake_minimum_required(VERSION 3.5)

project(DeskXiuxianPet VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 设置Qt的qmake可执行文件路径
if(UNIX)
    # 如果是Unix系统，设置Qt的qmake可执行文件路径
    set(QT_QMAKE_EXECUTABLE "/opt/Qt5.12.0/5.12.0/gcc_64/bin/qmake")
    set(Qt5_DIR "/opt/Qt5.12.0/5.12.0/gcc_64/lib/cmake/Qt5")
    set(CMAKE_PREFIX_PATH "/opt/Qt5.12.0/5.12.0/gcc_64")
elseif(WIN32)
    # 如果是Windows系统，设置Qt的qmake可执行文件路径
    set(QT_QMAKE_EXECUTABLE "D:/Qt/Qt5.0.12/5.12.0/mingw73_64/bin/qmake.exe")
    set(Qt5_DIR "D:/Qt/Qt5.12.0/5.12.0/mingw73_64/lib/cmake/Qt5")
    set(CMAKE_PREFIX_PATH "D:/Qt/Qt5.12.0/5.12.0/mingw73_64")
endif()
#find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
#find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Sql Network WebSockets)
#find_package(Qt5 COMPONENTS Core Gui Sql Network Widgets WebSockets Qml Quick REQUIRED)

file(GLOB_RECURSE SRC_SOURCE_FILES  # 非根目录下递归查找
        ${CMAKE_SOURCE_DIR}/public/*.h
        ${CMAKE_SOURCE_DIR}/public/*.cpp
        ${CMAKE_SOURCE_DIR}/widget/*.h
        ${CMAKE_SOURCE_DIR}/widget/*.cpp
        ${CMAKE_SOURCE_DIR}/common/*.h
        ${CMAKE_SOURCE_DIR}/common/*.cpp
        ${CMAKE_SOURCE_DIR}/role/*.h
        ${CMAKE_SOURCE_DIR}/role/*.cpp
        ${CMAKE_SOURCE_DIR}/server/*.h
        ${CMAKE_SOURCE_DIR}/server/*.cpp
        ${CMAKE_SOURCE_DIR}/filedata/*.h
        ${CMAKE_SOURCE_DIR}/filedata/*.cpp
        ${CMAKE_SOURCE_DIR}/logger/*.h
        ${CMAKE_SOURCE_DIR}/logger/*.cpp
        ${CMAKE_SOURCE_DIR}/progress/*.h
        ${CMAKE_SOURCE_DIR}/progress/*.cpp
        ${CMAKE_SOURCE_DIR}/business/*.h
        ${CMAKE_SOURCE_DIR}/business/*.cpp
        )

set(PROJECT_SOURCES
        main.cpp
        widget.cpp
        widget.h
        interface_manager.h
        interface_manager.cpp
        #        ${CMAKE_SOURCE_DIR}/public/error_code.h
)


if(ANDROID)
    add_library(DeskXiuxianPet SHARED
            ${PROJECT_SOURCES}
            message("安卓系统")
    )
else()
    message("非安卓系统 修仙模式")
    add_executable(DeskXiuxianPet
            ${PROJECT_SOURCES}
            ${SRC_SOURCE_FILES}
            img.qrc
    )
endif()


target_link_libraries(DeskXiuxianPet PRIVATE Qt5::Widgets)

set_target_properties(DeskXiuxianPet PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS DeskXiuxianPet
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(DeskXiuxianPet)
endif()
