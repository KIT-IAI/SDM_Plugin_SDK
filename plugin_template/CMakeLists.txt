# CMakeList.txt: CMake-Projektdatei der obersten Ebene. Führen Sie hier die globale Konfiguration aus,
# und schließen Sie Unterprojekte ein.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

set(IFCEXPLORER_TEST_DIR "unknown" CACHE PATH "directory with IFCExplorer binary")

if (NOT IFCEXPLORER_TEST_DIR STREQUAL "unknown")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${IFCEXPLORER_TEST_DIR})
endif()

project (myPlugin)

# Schließen Sie Unterprojekte ein.
add_subdirectory(myPlugin)