
#------------------------------------------
#   List source files
file(GLOB _headers "${PROJECT_SOURCE_DIR}/txt_table/*.h")
file(GLOB _src "${PROJECT_SOURCE_DIR}/txt_table/*.cpp")
set(TXT_TABLE_SRC_FILES
	${_headers}
	${_src}	
	${PROJECT_SOURCE_DIR}/txt_table/config.h.in
    ${PROJECT_SOURCE_DIR}/txt_table/CMakeLists.txt 
	)
set(TXT_TABLE_SRC_FILES ${TXT_TABLE_SRC_FILES} PARENT_SCOPE)
configure_file(${PROJECT_SOURCE_DIR}/txt_table/config.h.in "${PROJECT_BINARY_DIR}/txt_table/config.h" @ONLY)

#------------------------------------------
#   Add export macro and
#       remove useless warnings
if(WIN32)
    # remove warning C4275: se ha utilizado una interfaz no de DLL class
    # remove warning C4996: 'standard function': This function or variable may be unsafe...
    # remove warning C4251: 'atribute' : class 'name' necesita tener una interfaz DLL...
    add_definitions(-D_CRT_SECURE_NO_WARNINGS /wd4275 /wd4251)
else()
    list( APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")
endif(WIN32)

if (NOT BIICODE)
    include (GenerateExportHeader)
    include(../depends/cmake/use_precompiled_header2.cmake)


    # Look for boost
    include(../depends/cmake/boost_install.txt)
    BoostInstall()

    include_directories( ${Boost_INCLUDE_DIRS} )

    
    #------------------------------------------
    #        Build a library
    add_definitions(-D_UNICODE -DUNICODE)
    add_compiler_export_flags()
    add_library(txt_table SHARED ${TXT_TABLE_SRC_FILES})
    generate_export_header(txt_table)

    use_precompiled_header2(
        txt_table
        "stdafx.h"
        "stdafx.cpp"
        ${_src}	
        )
	
    set_target_properties(txt_table PROPERTIES
      PUBLIC_HEADER "api.h;txttable_parser.h;field.h;exceptions.h;field_subheader.h;field_vector.h;row.h;${CMAKE_CURRENT_BINARY_DIR}/config.h;${CMAKE_CURRENT_BINARY_DIR}/txt_table_export.h;"
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

endif()