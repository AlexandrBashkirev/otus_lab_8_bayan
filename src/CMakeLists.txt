find_package(Boost COMPONENTS system REQUIRED)
find_package(Boost COMPONENTS filesystem REQUIRED)
find_package(Boost COMPONENTS program_options REQUIRED)
find_package(Boost COMPONENTS regex REQUIRED)

include_directories(${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src)

list(APPEND ${PROJECT_NAME}_SOURCES
    bayan_main.cpp
    crc_hasher.cpp
    duplicate_searcher.cpp
    md5_hasher.cpp
    search_arg_builder.cpp
)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

set_target_properties(${PROJECT_NAME} PROPERTIES
	COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK)

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC 
	${Boost_LIBRARIES})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)