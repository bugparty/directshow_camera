cmake_minimum_required(VERSION 3.5)

#******Project******
project(directshow_camera LANGUAGES CXX)
# Set Window SDK Path. Change it to your Window SDK Path
 set(CMAKE_WINDOWS_KITS_10_DIR "C:/Program Files (x86)/Windows Kits/10") 
 # Set vcpkg path. Change here if the vcpkg folder is not located in your solution folder.
set(VCPKG_PATH d:/vcpkg)

set(CMAKE_TOOLCHAIN_FILE
    ${VCPKG_PATH}/scripts/buildsystems/vcpkg.cmake
    CACHE STRING "Vcpkg toolchain file")
#******Setting******
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#  C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
option(ENABLE_OPENCV "enable opencv support" ON)

set(CONFIG_HEADER_DIR ${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME})
file(REMOVE ${CONFIG_HEADER_DIR}/ds_libs_setting.h)
if (ENABLE_OPENCV)
  set(HAS_OPENCV true)
endif()
configure_file(include/directshow_camera/ds_libs_setting.h.in include/directshow_camera/ds_libs_setting.h)
include_directories(${CONFIG_HEADER_DIR})

# Check static library or executable
if(NOT ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    set(DIRECTSHOWCAMERA_AS_STATIC_LIBRARY TRUE)
endif()

# Get this CMakeLists location
set(DIRECTSHOWCAMERA_ROOT_PATH ${CMAKE_SOURCE_DIR})

# Add cmake module
list(APPEND CMAKE_MODULE_PATH "${DIRECTSHOWCAMERA_ROOT_PATH}/cmake")
if(ENABLE_OPENCV)
 include(InstallVcpkgOpenCV)
endif()

include(AddVcpkg)
include(AddWin10SDK)

#******Source******
if (${DIRECTSHOWCAMERA_AS_STATIC_LIBRARY}) 
    # ---Static library---

    #******Source******
    add_subdirectory("./src")

else()
    # ---Build example and test---

    # ******OpenCV and Window SDK******

    #   Set vcpkg as submodule. See cmake/AddVcpkg.cmake
    add_vcpkg()

    #   Set Window SDK path. See cmake/AddWin10SDK.cmake
    add_window10_sdk()

    # OpenCV
    if(ENABLE_OPENCV)
    #   Install OpenCV in vcpkg. See cmake/InstallVcpkgOpenCV.cmake
     install_vcpkg_opencv()
    #   Link OpenCV 
     include_directories( ${OpenCV_INCLUDE_DIRS} )
     link_directories( ${OpenCV_LIB_DIR} )
    endif()


    #******Source******

    add_subdirectory("./src")

    #******Example******
    if(ENABLE_OPENCV)
        add_subdirectory("./examples")
    endif()
    #******Test******


    if(BUILD_TESTING)
        find_package(GTest CONFIG REQUIRED)
        enable_testing()
        add_subdirectory("./test")
    endif()

    add_subdirectory("./experiments")
endif()