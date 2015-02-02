include (GenerateExportHeader)
include(../depends/cmake/use_precompiled_header2.cmake)

if(NOT WIN32) # On Visual Studio, C++0x features are enabled by default
	# Enable C++11
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

#------------------------------------------
#   List source files
file(GLOB _headers "*.h")
file(GLOB _src "*.cpp")
set(SRC_FILES
	${_headers}
	${_src}	
	CMakeLists.txt
    config.h.in
	)

# Look for boost
#include(../depends/cmake/boost_install.txt)
#BoostInstall()

#include_directories( ${Boost_INCLUDE_DIRS} )

#------------------------------------------
#   Add export macro and
#       remove useless warnings

if(WIN32)
# remove warning C4275: se ha utilizado una interfaz no de DLL class
# remove warning C4996: 'standard function': This function or variable may be unsafe...
# remove warning C4251: 'atribute' : class 'name' necesita tener una interfaz DLL...

add_definitions(-D_CRT_SECURE_NO_WARNINGS /wd4275 /wd4251)
endif(WIN32)

#macro
#ConfigFile()
configure_file(config.h.in "${CMAKE_CURRENT_BINARY_DIR}/config.h" @ONLY)


#------------------------------------------
#        Build a library
add_definitions(-D_UNICODE -DUNICODE)
add_compiler_export_flags()
add_library(txt_table SHARED ${SRC_FILES})
generate_export_header(txt_table)

use_precompiled_header2(
    txt_table
    "stdafx.h"
    "stdafx.cpp"
    ${_src}	
    )
	
set_target_properties(txt_table PROPERTIES
  PUBLIC_HEADER "api.h;txttable_parser.h;field.h;exceptions.h;field_subheader.h;field_vector.h;${CMAKE_CURRENT_BINARY_DIR}/config.h;${CMAKE_CURRENT_BINARY_DIR}/txt_table_export.h;"
  LINKER_LANGUAGE CXX
  FOLDER "core/service")

  
install(TARGETS txt_table
  # IMPORTANT: Add the txt_table library to the "export-set"
  EXPORT txt_table-targets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR}" COMPONENT lib  
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/txt_table"
    COMPONENT dev)
