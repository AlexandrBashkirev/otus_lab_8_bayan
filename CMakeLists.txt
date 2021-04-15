cmake_minimum_required(VERSION 3.2)

project(bayan VERSION 0.0.1)

configure_file(version.h.in ${PROJECT_SOURCE_DIR}/version.h)

include_directories(${CMAKE_BINARY_DIR})

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT alexandr.bashkirev@gmail.com)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)