cmake_minimum_required(VERSION 2.8)
project(txt_table CXX)

set(TXT_TABLE_MAJOR_VERSION 1)
set(TXT_TABLE_MINOR_VERSION 0)
set(TXT_TABLE_PATCH_VERSION 0)
set(TXT_TABLE_VERSION
  ${TXT_TABLE_MAJOR_VERSION}.${TXT_TABLE_MINOR_VERSION}.${TXT_TABLE_PATCH_VERSION})

# Set default for CMAKE_INSTALL_PREFIX
SET(CORE_INSTALL_PREFIX "C:/libraries/core" CACHE PATH "Prefix prepended to
install directories")
SET(CMAKE_INSTALL_PREFIX "${CORE_INSTALL_PREFIX}" CACHE INTERNAL "Prefix
prepended to install directories" FORCE)
  
# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH
  "Installation directory for header files")
if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR CMake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/CMake/txt_table)
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH
  "Installation directory for CMake files")
  
# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

# set up include-directories
include_directories(
  "${PROJECT_SOURCE_DIR}"   # to find txt_table/txttable_parser.h
  "${PROJECT_BINARY_DIR}")  # to find txt_table/config.h

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  
# Add sub-directories
add_subdirectory(txt_table)
OPTION(BUILD_EXAMPLES "Build txt_table examples" OFF)
if(${BUILD_EXAMPLES})
	add_subdirectory(examples) 
endif()

# The interesting stuff goes here
# ===============================

# Add all targets to the build-tree export set
export(TARGETS txt_table
  FILE "${PROJECT_BINARY_DIR}/txt_table-targets.cmake")

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE txt_table)

# Create the txt_table-config.cmake and txt_table-config-version files
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
   "${INSTALL_INCLUDE_DIR}")
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(txt_table-config.cmake.in
  "${PROJECT_BINARY_DIR}/txt_table-config.cmake" @ONLY)
# ... for the install tree
set(CONF_INCLUDE_DIRS "\${TXT_TABLE_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(txt_table-config.cmake.in
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/txt_table-config.cmake" @ONLY)
# ... for both
configure_file(txt_table-config-version.cmake.in
  "${PROJECT_BINARY_DIR}/txt_table-config-version.cmake" @ONLY)

# Install the txt_table-config.cmake and txt_table-config-version.cmake
install(FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/txt_table-config.cmake"
  "${PROJECT_BINARY_DIR}/txt_table-config-version.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

# Install the export set for use with the install-tree
install(EXPORT txt_table-targets DESTINATION
  "${INSTALL_CMAKE_DIR}" COMPONENT dev)

  
message(STATUS "Files will be installed at ${CMAKE_INSTALL_PREFIX}")