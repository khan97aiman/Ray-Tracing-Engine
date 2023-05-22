set(PROJECT_NAME GUI)

################################################################################
# Source groups
################################################################################

# if OS is Windows, only then add Imgui (UPDATE THIS)
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
set(ImGui
    "../Middleware/ImGui/imgui.cpp"
    "../Middleware/ImGui/imgui.h"
    "../Middleware/ImGui/imgui_demo.cpp"
    "../Middleware/ImGui/imgui_draw.cpp"
    "../Middleware/ImGui/imgui_impl_win32.cpp"
    "../Middleware/ImGui/imgui_impl_win32.h"
    "../Middleware/ImGui/imgui_internal.h"
    "../Middleware/ImGui/imgui_widgets.cpp" 
    "../Middleware/ImGui/imgui_tables.cpp" 
    "../Middleware/ImGui/imstb_rectpack.h" 
    "../Middleware/ImGui/imstb_textedit.h" 
    "../Middleware/ImGui/imstb_truetype.h" 
    "../Middleware/ImGui/imconfig.h" 
)
source_group("ImGui Files" FILES ${ImGui})

# Adding graphics API implementation for ImGui
if(GRAPHICS_API STREQUAL "VULKAN")
    set(ImGui_Graphics_API_Impl
        "../Middleware/ImGui/imgui_impl_vulkan.cpp"
        "../Middleware/ImGui/imgui_impl_vulkan.h"
        "ImGuiObject_VulkanWin32.h"
        "ImGuiObject_VulkanWin32.cpp"
    )
elseif(GRAPHICS_API STREQUAL "OPENGL3")
    set(ImGui_Graphics_API_Impl
        "../Middleware/ImGui/imgui_impl_opengl3.cpp"
        "../Middleware/ImGui/imgui_impl_opengl3.h"
        "ImGuiObject_OpenGL3Win32.h"
        "ImGuiObject_OpenGL3Win32.cpp"
    )
endif()

source_group("ImGui Files\\ImGui Graphics API Implementation" FILES ${ImGui_Graphics_API_Impl})

set(ALL_FILES
    ${ImGui}
    ${ImGui_Graphics_API_Impl}
)
else()
message("Critical Warning: Imgui files are not included!")
endif()
#set_source_files_properties(${ALL_FILES} PROPERTIES LANGUAGE CXX)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE GUI)

set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
)
################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "_CRT_SECURE_NO_WARNINGS;"
    "_MBCS"
    "NOMINMAX"
)

################################################################################
# Compile and link options
################################################################################

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /Od
        >
        $<$<CONFIG:Release>:
            /O2;
            /Oi;
            /Gy
        >
        /permissive-;
        /std:c++latest;
        /sdl;
        /W3;
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        ${DEFAULT_CXX_EXCEPTION_HANDLING}
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            /OPT:REF;
            /OPT:ICF
        >
    )
endif()

include_directories("./")
include_directories("../Middleware/ImGui/")
include_directories("../GameEngine/Maths/")
include_directories("../GameEngine/EntityComponents/")
include_directories("../GameEngine/WindowingAndInput/")
include_directories("../GameEngine/WindowingAndInput/Win32/")

set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "GameEngine"
)

target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")