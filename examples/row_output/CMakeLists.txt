
#------------------------------------------
#   List source files
file(GLOB _headers "${PROJECT_SOURCE_DIR}/examples/row_output/*.h")
file(GLOB _src "${PROJECT_SOURCE_DIR}/examples/row_output/*.cpp")
set(EXAMPLES_ROW_OUTPUT_SRC_FILES
	${_headers}
	${_src}	
	)
set(EXAMPLES_ROW_OUTPUT_SRC_FILES ${EXAMPLES_ROW_OUTPUT_SRC_FILES} PARENT_SCOPE)

if(WIN32)
    # remove warning C4275: se ha utilizado una interfaz no de DLL class
    # remove warning C4996: 'standard function': This function or variable may be unsafe...
    # remove warning C4251: 'atribute' : class 'name' necesita tener una interfaz DLL...
    add_definitions(-D_CRT_SECURE_NO_WARNINGS /wd4275 /wd4251)
endif(WIN32)


if (NOT BIICODE)
    # Look for boost
    include(../../depends/cmake/boost_install.txt)
    BoostInstall()

    include_directories( ${Boost_INCLUDE_DIRS} )
    
    add_executable(row_output ${EXAMPLES_ROW_OUTPUT_SRC_FILES})
    target_link_libraries(row_output txt_table)
     
    set_target_properties(row_output PROPERTIES
      LINKER_LANGUAGE CXX
      FOLDER "examples")

    add_custom_command(TARGET row_output POST_BUILD    # Adds a post-build event to MyTest
        COMMAND ${CMAKE_COMMAND} -E copy_if_different       # which executes "cmake - E copy_if_different..."
            $<TARGET_FILE:txt_table>                        # <--this is in-file
            $<TARGET_FILE_DIR:row_output>)             # <--this is out-file path
        
    add_custom_command(TARGET row_output POST_BUILD    # Adds a post-build event to MyTest
        COMMAND ${CMAKE_COMMAND} -E copy_directory          # which executes "cmake - E copy_if_different..."
            ${CMAKE_CURRENT_SOURCE_DIR}/../data             # <--this is in-file
            $<TARGET_FILE_DIR:row_output>/../data)     # <--this is out-file path
            
    set_property(TARGET row_output PROPERTY CXX_STANDARD 11)
endif()
