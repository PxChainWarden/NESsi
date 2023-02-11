cmake_minimum_required(VERSION 3.14)

project(deneme VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)

set(PROJECT_SOURCES
        src/main.cpp
        qml.qrc
        src/testclass.cpp
        inc/testclass.h
        src/Bus.cpp
        inc/Bus.h
        src/Px6502CPU.cpp
        inc/Px6502CPU.h
        src/PxCartridge.cpp
        inc/PxCartridge.h
        src/Px2C02PPU.cpp
        inc/Px2C02PPU.h
        src/registers/Register.cpp
        inc/registers/Register.h
        src/registers/PpuAddressRegister.cpp
        inc/registers/PpuAddressRegister.h
        src/registers/PpuControlRegister.cpp
        inc/registers/PpuControlRegister.h
        src/registers/PpuMaskRegister.cpp
        inc/registers/PpuMaskRegister.h
        src/mappers/PxMapper.cpp
        inc/mappers/PxMapper.h
        src/mappers/Mapper000.cpp
        inc/mappers/Mapper000.h
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(deneme
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET deneme APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(deneme SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(deneme
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(deneme
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

target_include_directories(deneme PRIVATE ${PROJECT_SOURCE_DIR}/mappers)
target_include_directories(deneme PRIVATE ${PROJECT_SOURCE_DIR}/inc)

set_target_properties(deneme PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS deneme
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(deneme)
    qt_finalize_executable(deneme)
endif()
