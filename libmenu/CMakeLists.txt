cmake_minimum_required(VERSION 3.10)

project(menu VERSION 1.0.0)

set (TARGET consolemenu)

set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(HEADERS_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(SOURCES 
	${SRC_DIR}/menu.cpp 
	${SRC_DIR}/item.cpp 
	${SRC_DIR}/pager.cpp 
	${SRC_DIR}/term.cpp 
)

message("SRC_DIR = ${SRC_DIR}\nHEADERS_DIR = ${HEADERS_DIR}")
configure_file(
	${CMAKE_CURRENT_LIST_DIR}/version.hpp.in
	${HEADERS_DIR}/version.hpp
	)

list(APPEND CMAKE_MODULE_PATH $ENV{HOME}/cmake_modules)

add_compile_options(
	-fPIC
)

add_library(${TARGET} ${SOURCES})

#find_package(Boost REQUIRED COMPONENTS program_options)

#if(Boost_FOUND)
#	message("Boost_LIBRARIES = " ${Boost_LIBRARIES})
#	target_link_libraries(${TARGET} ${Boost_LIBRARIES})
#	#target_include_directories(${TARGET} PUBLIC ${Boost_INCLUDE_DIRS})
#else()
#	message("Не получится собрать приложение\n, не найден Boost")
#	exit()
#endif()

#find_package(Soci)
#if(SOCI_FOUND)
#	target_include_directories(${TARGET} PRIVATE ${SOCI_INCLUDE_DIR})
#	target_link_libraries(${TARGET} ${SOCI_LIBRARY})
#	target_link_libraries(${TARGET} ${SOCI_mysql_PLUGIN})
#	target_link_libraries(${TARGET} ${SOCI_postgresql_PLUGIN})
#else()
#	message("Soci not found")
#endif()

target_include_directories(${TARGET} PRIVATE ${HEADERS_DIR})
#target_include_directories(${TARGET} PRIVATE ${CMAKE_HOME_DIRECTORY}/../../lib/soci_bd/include)

#target_link_libraries(${TARGET} ${CMAKE_HOME_DIRECTORY}/../../lib/soci_bd/lib/libsoci_connection.a)


set_target_properties(
	${TARGET} PROPERTIES
	CXX_STANDARD 17	#Собирать в соответствии со стандартом c++17
	)
