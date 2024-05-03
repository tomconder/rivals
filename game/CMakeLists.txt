include(GNUInstallDirs)

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

file(
        GLOB HEADER_FILES
        LIST_DIRECTORIES false
        src/*.hpp)

file(
        GLOB SOURCE_FILES
        LIST_DIRECTORIES false
        src/*.cpp)

file(
        GLOB ASSETS
        LIST_DIRECTORIES false
        assets/*)

if (APPLE)
  message(STATUS "Including OSX platform files")
  file(GLOB OSX_HEADERS src/platform/osx/*.hpp)
  list(APPEND HEADER_FILES ${OSX_HEADERS})
  file(GLOB OSX_SOURCES src/platform/osx/*.cpp)
  list(APPEND SOURCE_FILES ${OSX_SOURCES})
endif ()

if (MSVC)
  message(STATUS "Including Windows platform files")
  file(GLOB WIN_HEADERS src/platform/windows/*.hpp)
  list(APPEND HEADER_FILES ${WIN_HEADERS})
  file(GLOB WIN_SOURCES src/platform/windows/*.cpp)
  list(APPEND SOURCE_FILES ${WIN_SOURCES})
endif ()

if (UNIX AND NOT APPLE)
  message(STATUS "Including Linux platform files")
  file(GLOB LINUX_HEADERS src/platform/linux/*.hpp)
  list(APPEND HEADER_FILES ${LINUX_HEADERS})
  file(GLOB LINUX_SOURCES src/platform/linux/*.cpp)
  list(APPEND SOURCE_FILES ${LINUX_SOURCES})
endif ()

find_package(SDL2 CONFIG REQUIRED)
find_package(Stb REQUIRED)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/rivals)

if (WIN32)
  set_source_files_properties(rivals.rc PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
  add_executable(rivals WIN32 ${SOURCE_FILES} ${HEADER_FILES} rivals.rc)
  target_include_directories(rivals PRIVATE bundle/icons)
elseif (APPLE)
  set(MACOSX_BUNDLE_ICON_FILE rivals.icns)
  set(MACOSX_BUNDLE_BUNDLE_NAME ${CMAKE_PROJECT_NAME})
  set(MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION})
  set(MACOSX_BUNDLE_LONG_VERSION_STRING ${PROJECT_VERSION})
  set(MACOSX_BUNDLE_COPYRIGHT ${COPYRIGHT})

  set(app_icon_macos "bundle/icons/rivals.icns")
  set_source_files_properties(
          ${app_icon_macos} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources"
          SKIP_PRECOMPILE_HEADERS ON)
  add_executable(rivals MACOSX_BUNDLE ${SOURCE_FILES} ${HEADER_FILES} ${app_icon_macos})
else ()
  add_executable(rivals ${SOURCE_FILES} ${HEADER_FILES})
endif ()

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

target_include_directories(rivals PUBLIC src)
target_include_directories(rivals SYSTEM PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(rivals PRIVATE $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main> $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>)

if (APPLE)
  add_custom_command(
          TARGET rivals
          POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_BUNDLE_CONTENT_DIR:rivals>/Resources
          COMMENT "Copying assets to bundle content folder"
          VERBATIM DEPENDS ${ASSETS})

  install(TARGETS rivals BUNDLE DESTINATION .)

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
