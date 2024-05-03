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

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/rivals)

if (WIN32)
  set_source_files_properties(maze.rc PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
  add_executable(rivals WIN32 ${SOURCE_FILES} ${HEADER_FILES} rivals.rc)
  target_include_directories(rivals PRIVATE bundle/icons)
elseif (APPLE)
  add_executable(rivals MACOSX_BUNDLE ${SOURCE_FILES} ${HEADER_FILES})
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

  install(TARGETS game BUNDLE DESTINATION .)

  set(APPS "$<TARGET_BUNDLE_DIR:rivals>")

  install(CODE "
        set(BU_CHMOD_BUNDLE_ITEMS ON)
        include(BundleUtilities)
        fixup_bundle(\"${APPS}\" \"${LIBS}\" \"${DIRS}\"\)"
          COMPONENT Runtime
  )

    set(CPACK_GENERATOR "DRAGNDROP")
    include(CPack)
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