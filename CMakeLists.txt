cmake_minimum_required(VERSION 3.12)

project(mal-toolkit LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB_RECURSE MALTOOLKIT_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/mal-toolkit/*.*"
)

add_library(mal-toolkit ${MALTOOLKIT_SOURCES})

target_include_directories(mal-toolkit PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/mal-toolkit)


find_package(Boost COMPONENTS serialization HINTS "
    C:/" 
    "C:/Boost")

if(Boost_FOUND)
    message(STATUS "Boost found: ${Boost_VERSION}")
    target_include_directories(mal-toolkit PUBLIC ${Boost_INCLUDE_DIRS})
    target_link_libraries(mal-toolkit PUBLIC ${Boost_LIBRARIES})
else()
    message(WARNING "Boost not found")
endif()



if(NOT TARGET spdlog)
    find_package(spdlog QUIET)

    if(NOT spdlog_FOUND)
        message(STATUS "spdlog not found. Using submodule...")

        add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/third_party/spdlog/" EXCLUDE_FROM_ALL)

        target_include_directories(spdlog INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/third_party/spdlog/include")
    endif()
endif()

target_link_libraries(mal-toolkit PUBLIC spdlog::spdlog_header_only)