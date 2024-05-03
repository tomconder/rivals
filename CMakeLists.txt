cmake_minimum_required(VERSION 3.17)
project(rivals
        VERSION 1.0
        DESCRIPTION "A dungeon crawl with corporate ambitions"
        HOMEPAGE_URL "https://gitub.com/tomconder/rivals"
        LANGUAGES C CXX)

set(COPYRIGHT "Copyright 2024 Tom Conder")

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

file(
        GLOB HEADER_FILES
        LIST_DIRECTORIES false
        src/include/*.h)

file(
        GLOB SOURCE_FILES
        LIST_DIRECTORIES false
        src/*.cpp)

file(
        GLOB ASSETS
        LIST_DIRECTORIES false
        assets/*)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_IMAGE CONFIG REQUIRED)

add_executable(rivals ${SOURCE_FILES} ${HEADER_FILES})

set_target_properties(rivals PROPERTIES CXX_STANDARD 23)

if (MSVC)
  # incremental builds
  target_compile_options(rivals PUBLIC $<$<NOT:$<CONFIG:RELEASE>>:/Zi>)
  target_link_options(rivals PUBLIC $<IF:$<CONFIG:RELEASE>,/INCREMENTAL:NO,/INCREMENTAL>)

  # hardening
  message(STATUS "Applying Windows hardening support")
  target_compile_options(rivals PUBLIC $<$<NOT:$<CONFIG:DEBUG>>:/DYNAMICBASE /guard:cf>)
  target_link_options(rivals PUBLIC "/NXCOMPAT /CETCOMPAT")
endif ()

target_include_directories(rivals PUBLIC src/include)

target_link_libraries(rivals PRIVATE $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main> $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>)
target_link_libraries(rivals PRIVATE $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)

if (APPLE)
  add_custom_command(
          TARGET rivals
          POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_BUNDLE_CONTENT_DIR:rivals>/Resources
          COMMENT "Copying assets to bundle content folder"
          VERBATIM DEPENDS ${ASSETS})

  set(APPS "$<TARGET_BUNDLE_DIR:rivals>")

  install(CODE "
        set(BU_CHMOD_BUNDLE_ITEMS ON)
        include(BundleUtilities)
        fixup_bundle(\"${APPS}\" \"${LIBS}\" \"${DIRS}\"\)"
          COMPONENT Runtime
  )
else ()
  add_custom_command(
          TARGET rivals
          POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:rivals>/assets
          COMMENT "Copying assets to target folder"
          VERBATIM DEPENDS ${ASSETS})

  install(TARGETS rivals RUNTIME DESTINATION .)
  install(FILES $<TARGET_RUNTIME_DLLS:rivals> DESTINATION .)
  install(DIRECTORY assets DESTINATION .)
endif ()
