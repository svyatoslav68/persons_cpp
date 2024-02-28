cmake_minimum_required(VERSION 3.10)

project(persons VERSION 0.0.2)

set(TARGET persons)

set(SRC_DIR ${CMAKE_HOME_DIRECTORY}/src)
set(HEADERS_DIR ${CMAKE_HOME_DIRECTORY}/headers)

configure_file(
	${CMAKE_HOME_DIRECTORY}/version.hpp.in
	${HEADERS_DIR}/version.hpp
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB SOURCES
	${SRC_DIR}/*.cpp)
message("Sources files: ${SOURCES}")

list(APPEND CMAKE_MODULE_PATH $ENV{HOME}/cmake_modules)

add_executable(${TARGET} ${SOURCES})

target_include_directories(${TARGET} PRIVATE ${HEADERS_DIR})
# В добавление в список поиска каталога с заголовками mysql
message("CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}" )
find_package(MariaDBClient REQUIRED)
if(MariaDBClient_FOUND)
	target_include_directories(${TARGET} PUBLIC ${MariaDBClient_INCLUDE_DIR})
	message("MariaDBClient_LIBRARIES = ${MariaDBClient_LIBRARIES}")
	message("MariaDBClient_INCLUDE_DIR = ${MariaDBClient_INCLUDE_DIR}")
else()
	message("Не найден MariaDBClient,\nбудет предпринята попытка найти MySQL-клиент.")
	find_package(MySql REQUIRED)
	if(MYSQL_FOUND)
		include_directories(${MYSQL_INCLUDE_DIR})
		message("Найден MySQL header ${MYSQL_INCLUDE_DIR}")
	else()
		message("Никто не найден. (MariaDB, MYSQL)")
		exit()
	endif()
	exit()
endif()

find_package(Boost REQUIRED COMPONENTS program_options date_time)
find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui) 

if(Boost_FOUND)
	message("Boost_LIBRARIES = " ${Boost_LIBRARIES})
	target_link_libraries(${TARGET} ${Boost_LIBRARIES})
	#target_include_directories(${TARGET} PUBLIC ${Boost_INCLUDE_DIRS})
else()
	message("Не получится собрать приложение\n, не найден Boost")
	exit()
endif()

if(Qt5_FOUND)
	message("Qt_LIBRARIES = " ${Qt5_LIBRARIES})
	target_link_libraries(${TARGET} Qt5::Widgets Qt5::Core Qt5::Gui)
else()
	message("Не получится собрать приложение\n, не найден Qt5")
	exit()
endif()

set_target_properties(
	${TARGET_APP} PROPERTIES
	CXX_STANDARD 17	#Собирать в соответствии со стандартом c17
	C_STANDARD	11
	)
