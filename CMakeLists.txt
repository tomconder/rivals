cmake_minimum_required(VERSION 3.17)
project(dcj21 CXX C)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/animatedsprite.cpp src/dungeoncrawler.cpp src/enemy.cpp src/engine.cpp src/graphics.cpp src/input.cpp src/level.cpp src/main.cpp src/map.cpp src/mapcursor.cpp src/player.cpp src/sprite.cpp)
include_directories(src/include)

if (EMSCRIPTEN)
  message("Building for emscripten")

  set(CMAKE_EXECUTABLE_SUFFIX ".html")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O2 -s USE_SDL=2 -s USE_SDL_IMAGE=2")

  add_executable(${PROJECT_NAME} ${SOURCE_FILES})

  set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/html)

  set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-std=c++17 -O2 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s \"SDL2_IMAGE_FORMATS=['png']\" --preload-file ${PROJECT_SOURCE_DIR}/build/assets@assets")
else (EMSCRIPTEN)
  set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
  find_package(SDL2 REQUIRED)
  find_package(SDL2_IMAGE REQUIRED)

  # for debugging
  # include(CMakePrintHelpers)
  # cmake_print_variables(SDL2_INCLUDE_DIR)
  # cmake_print_variables(SDL2_LIBRARY)

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++17")

  add_executable(${PROJECT_NAME} ${SOURCE_FILES})

  target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIR})
  target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_IMAGE_INCLUDE_DIR})

  target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
  target_link_libraries(${PROJECT_NAME} ${SDL2_IMAGE_LIBRARY})

  set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
  set(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})
endif (EMSCRIPTEN)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")

# copy assets
file(GLOB ASSETS assets/*)
file(COPY ${ASSETS} DESTINATION ${PROJECT_SOURCE_DIR}/build/assets)
