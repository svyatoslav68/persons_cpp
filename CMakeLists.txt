cmake_minimum_required(VERSION 3.10)

project(persons VERSION 0.0.3)

set(TARGET persons)

set(SRC_DIR ${CMAKE_HOME_DIRECTORY}/src)
set(HEADERS_DIR ${CMAKE_HOME_DIRECTORY}/headers)

configure_file(
	${CMAKE_HOME_DIRECTORY}/version.hpp.in
	${HEADERS_DIR}/version.hpp
)

#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC ON)

file(GLOB SOURCES
	${SRC_DIR}/*.cpp)
message("Sources files: ${SOURCES}")

list(APPEND CMAKE_MODULE_PATH $ENV{HOME}/cmake_modules)

add_executable(${TARGET} ${SOURCES})

target_include_directories(${TARGET} PRIVATE ${HEADERS_DIR})

find_package(Boost REQUIRED COMPONENTS program_options date_time)
#find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui) 

if(${Boost_FOUND})
    message("-- Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message("-- Boost_LIBRARIES: ${Boost_LIBRARIES}")
	message("Boost_LIBRARIES = " ${Boost_LIBRARIES})
	target_link_libraries(${TARGET} ${Boost_LIBRARIES})
	#target_include_directories(${TARGET} PUBLIC ${Boost_INCLUDE_DIRS})
else()
	message("?? Не получится собрать приложение\n, не найден Boost")
	exit()
endif()

#if(${Qt5_FOUND})
#	message("Qt_LIBRARIES = " ${Qt5_LIBRARIES})
#	target_link_libraries(${TARGET} Qt5::Widgets Qt5::Core Qt5::Gui)
#else()
#	message("?? Не получится собрать приложение\n, не найден Qt5")
#	exit()
#endif()

find_package(Soci)
if(${SOCI_FOUND})
	#SET(SOCI_INCLUDE_DIRS "/usr/local/include/soci")
	#SET(SOCI_LIBRARY "")
    message("-- SOCI_INCLUDE_DIRS: ${SOCI_INCLUDE_DIRS}")
    message("-- SOCI_LIBRARY: ${SOCI_LIBRARY}")
    target_include_directories(${TARGET} PRIVATE ${SOCI_INCLUDE_DIRS})
    target_link_libraries(${TARGET} ${SOCI_LIBRARY})
else()
    message("?? Не найдена библиотека Soci")
endif()

set_target_properties(
	${TARGET} PROPERTIES
	CXX_STANDARD 17	#Собирать в соответствии со стандартом c17
	C_STANDARD	11
	)
