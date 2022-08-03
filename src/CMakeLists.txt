# header folder
SET(MY_HEADER_DIR ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})
SET(MY_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
# Get sources file
file(GLOB_RECURSE MY_SOURCE_FILES
    "*.h" "*.hpp" "*.cpp"
    "${MY_HEADER_DIR}/*.h" "${MY_HEADER_DIR}/*.hpp" "${MY_HEADER_DIR}/*.cpp"
)

if(NOT ENABLE_OPENCV)
list(REMOVE_ITEM MY_SOURCE_FILES ${MY_SOURCE_DIR}/uvc_camera_looper.cpp)
list(REMOVE_ITEM MY_SOURCE_FILES ${MY_HEADER_DIR}/uvc_camera_looper.h)
message("files ${MY_SOURCE_FILES}")
endif()
# Create static library
add_library(${PROJECT_NAME} SHARED STATIC ${MY_SOURCE_FILES})

# Make sure the compiler can find include files
target_include_directories (${PROJECT_NAME}
    PUBLIC
        ${MY_HEADER_DIR}
)