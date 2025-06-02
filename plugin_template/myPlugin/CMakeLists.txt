# CMakeList.txt: CMake-Projekt für "myPlugin". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

find_package(wxWidgets CONFIG REQUIRED)

add_library(myPlugin SHARED
            myPluginDlg.cpp
            myPluginDlg.h
            myPluginDlgImpl.cpp
            myPluginDlgImpl.h
            myPlugin.cpp
            myPlugin.h
            myClass.cpp
            myClass.h
            PluginObserver.cpp
            PluginObserver.h)

target_link_directories(myPlugin PRIVATE ${CMAKE_SOURCE_DIR}/lib)
target_include_directories(myPlugin PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_compile_options(myPlugin PRIVATE /utf-8)

if( CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_link_libraries(myPlugin PRIVATE ifcexplorer_plugin_d stdutils_d ifcdb_d gps_d Rpcrt4 glu32)
elseif( CMAKE_BUILD_TYPE STREQUAL "Release")
  target_link_libraries(myPlugin PRIVATE ifcexplorer_plugin stdutils ifcdb gps Rpcrt4 glu32)
else()
    MESSAGE( STATUS "CMAKE_BUILD_TYPE not set yet ${CMAKE_BUILD_TYPE}" )
endif()

target_link_libraries(myPlugin PRIVATE wx::core wx::base)

set_target_properties(myPlugin PROPERTIES VCPKG_MANIFEST_MODE TRUE)
