cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0042 NEW)
cmake_policy(SET CMP0091 NEW)

project(api_rate_limiter VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
add_definitions(-DNAPI_VERSION=9)

# Get node-addon-api include path
execute_process(
  COMMAND node -p "require('node-addon-api').include"
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE NODE_ADDON_API_DIR
)
string(REGEX REPLACE "[\r\n\"]" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})

# Include directories
include_directories(
  ${CMAKE_JS_INC}
  ${NODE_ADDON_API_DIR}
  ${NODE_ADDON_API_DIR}/..       # ✅ Required for napi.h
  ${CMAKE_SOURCE_DIR}/addons     # ✅ double check folder name is correct
  ${CMAKE_SOURCE_DIR}/addons/limiters
)

# Source files
file(GLOB SOURCE_FILES
  "${CMAKE_SOURCE_DIR}/addons/*.cpp"
  "${CMAKE_SOURCE_DIR}/addons/limiters/*.cpp"
)

# Create the shared library as Node addon
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

target_compile_definitions(${PROJECT_NAME} PRIVATE NAPI_CPP_EXCEPTIONS)
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})

# Copy built .node to dist/
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/dist
  COMMAND ${CMAKE_COMMAND} -E copy 
    $<TARGET_FILE:${PROJECT_NAME}> 
    ${CMAKE_SOURCE_DIR}/dist/${PROJECT_NAME}.node
)
