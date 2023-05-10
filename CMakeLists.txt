cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)
set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)

project(RealTimeRayTracing CXX)

################################################################################
# Output target arch type. Visual studio solution generator provides it.
################################################################################

message("${CMAKE_VS_PLATFORM_NAME} architecture in use")

################################################################################
# Check if host system's OS is Windows, then make a bool for building networking project
################################################################################
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
set(BUILD_NETWORKING CACHE BOOL FORCE)
endif()

################################################################################
# Global configuration types
################################################################################
#set(CMAKE_CONFIGURATION_TYPES
#    "Debug"
#    "Release"
#    CACHE STRING "" FORCE
#)

set(AVAILABLE_GRAPHICS_APIS
    "VULKAN"
    "OPENGL3"
    CACHE STRING "" FORCE
)

################################################################################
# Nuget packages function stub.
################################################################################
function(use_package TARGET PACKAGE VERSION)
    message(WARNING "No implementation of use_package. Create yours. "
                    "Package \"${PACKAGE}\" with version \"${VERSION}\" "
                    "for target \"${TARGET}\" is ignored!")
endfunction()

################################################################################
# Common utils
################################################################################
include(CMake/Utils.cmake)

################################################################################
# Additional Global Settings(add specific info there)
################################################################################
include(CMake/GlobalSettingsInclude.cmake OPTIONAL)

################################################################################
# Use solution folders feature
################################################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

################################################################################
# find relevant graphical APIs depending on which one is selected
################################################################################
add_compile_definitions(GRAPHICS_API=${GRAPHICS_API})
if(GRAPHICS_API STREQUAL "VULKAN")
    find_package(Vulkan REQUIRED)
endif()

set(ASSET_ROOT "${CMAKE_SOURCE_DIR}/Assets/" CACHE STRING "" FORCE)
add_compile_definitions(ASSETROOTLOCATION="${ASSET_ROOT}") 

################################################################################
# Sub-projects
################################################################################
add_subdirectory(GameEngine)

if(BUILD_NETWORKING)
    add_subdirectory(Networking)
endif()

if(GRAPHICS_API STREQUAL "VULKAN")
    add_subdirectory(VulkanRendering)
elseif(GRAPHICS_API STREQUAL "OpenGL3")
    add_subdirectory(OpenGLRendering)
endif()

add_subdirectory(SampleGame)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SampleGame)