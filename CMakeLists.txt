cmake_minimum_required(VERSION 3.24)

set(RIVALS_VERSION 1.0)

# increment this when we break backwards compatibility
set(RIVALS_SOVERSION 1)

project(rivals
        VERSION ${RIVALS_VERSION}
        DESCRIPTION "A dungeon crawl with corporate ambitions"
        HOMEPAGE_URL "https://gitub.com/tomconder/rivals"
        LANGUAGES C CXX)

if (WIN32)
  # accommodate missing version number values
  string(APPEND VERSION ${PROJECT_VERSION_MAJOR})
  if (PROJECT_VERSION_MINOR)
    string(APPEND VERSION ",${PROJECT_VERSION_MINOR}")
  else ()
    string(APPEND VERSION ",0")
  endif ()
  if (PROJECT_VERSION_PATCH)
    string(APPEND VERSION ",${PROJECT_VERSION_PATCH}")
  else ()
    string(APPEND VERSION ",0")
  endif ()
  if (PROJECT_VERSION_TWEAK)
    string(APPEND VERSION ",${PROJECT_VERSION_TWEAK}")
  else ()
    string(APPEND VERSION ",0")
  endif ()

  configure_file(bundle/resources/rivals.rc.in rivals.rc)
endif ()

set(COPYRIGHT "Copyright 2024 Tom Conder")

message(STATUS "Configuring ${PROJECT_NAME} ${PROJECT_VERSION}")

if (NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD
          23
          CACHE STRING "")
endif ()

if (CMAKE_CXX_STANDARD LESS 23)
  message(
          WARNING
          "Incompatible C++ standard ${CMAKE_CXX_STANDARD}. This project requires C++23"
  )
endif ()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set a default build type if none was specified See
# https://blog.kitware.com/cmake-and-the-default-build-type/ for details.
set(default_build_type "Release")

if (EXISTS "${CMAKE_SOURCE_DIR}/.git")
  set(default_build_type "Debug")
endif ()

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(
          STATUS
          "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE
          "${default_build_type}"
          CACHE STRING "Choose the type of build." FORCE)

  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif ()

# Generate compile_commands.json to help work with clang based tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enhance error reporting and compiler messages
set(CMAKE_COLOR_DIAGNOSTICS ON)

add_subdirectory(game)
