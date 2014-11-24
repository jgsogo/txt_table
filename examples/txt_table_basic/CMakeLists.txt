cmake_minimum_required(VERSION 2.8)

#------------------------------------------
#   List source files
file(GLOB _headers "*.h")
file(GLOB _src "*.cpp")
set(SRC_FILES
	${_headers}
	${_src}	
	)
	
include_directories( ${Boost_INCLUDE_DIRS} )

if(WIN32)
# remove warning C4275: se ha utilizado una interfaz no de DLL class
# remove warning C4996: 'standard function': This function or variable may be unsafe...
# remove warning C4251: 'atribute' : class 'name' necesita tener una interfaz DLL...
add_definitions(-D_CRT_SECURE_NO_WARNINGS /wd4275 /wd4251)
endif(WIN32)

add_executable(txt_table_basic ${SRC_FILES})
target_link_libraries(txt_table_basic txt_table)
 
set_target_properties(txt_table_basic PROPERTIES
  LINKER_LANGUAGE CXX
  FOLDER "examples")
 