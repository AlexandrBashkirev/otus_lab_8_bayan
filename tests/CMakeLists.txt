project(${PROJECT_NAME}_tests)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

include_directories(${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src)

list(APPEND ${PROJECT_NAME}_SOURCES
    test.cpp)

add_executable(${PROJECT_NAME}_tests ${${PROJECT_NAME}_SOURCES})

set_target_properties(${PROJECT_NAME}_tests PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)
set_target_properties(${PROJECT_NAME}_tests PROPERTIES
	COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK)


target_link_libraries(${PROJECT_NAME}_tests
	${Boost_LIBRARIES})

add_test(NAME ${PROJECT_NAME}_tests COMMAND ${PROJECT_NAME}_tests)