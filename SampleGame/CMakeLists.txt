set(PROJECT_NAME SampleGame)

################################################################################
# Source groups
################################################################################
if(BUILD_NETWORKING)
set(Header_Files
    "SinglePlayerGame.h"
    "SampleGame.h"
    "GameManager.h"
    "PlatformConfigurations.h"
    "GameAssets.h"
    "NetworkedGame.h"
    "NetworkPlayer.h"
    "EventListener.h"
)
else()
set(Header_Files
    "SinglePlayerGame.h"
    "SampleGame.h"
    "GameManager.h"
    "PlatformConfigurations.h"
    "GameAssets.h"
    "EventListener.h"
)
endif()
source_group("Header Files" FILES ${Header_Files})

if(BUILD_NETWORKING)
set(Source_Files
    "Main.cpp"
    "SinglePlayerGame.cpp"
    "SampleGame.cpp"
    "GameManager.cpp"
    "GameAssets.cpp"
    "NetworkedGame.cpp"
    "NetworkPlayer.cpp"
    "EventListener.cpp"
)
else()
set(Source_Files
    "Main.cpp"
    "SinglePlayerGame.cpp"
    "SampleGame.cpp"
    "GameManager.cpp"
    "GameAssets.cpp"
    "EventListener.cpp"
)
endif()

source_group("Source Files" FILES ${Source_Files})

set(GameObjects
    "./GameObjects/Box.h"
    "./GameObjects/Floor.h"
    "./GameObjects/Ink.h"
    "./GameObjects/HudElement.h"
    "./GameObjects/HudElement.cpp"
    "./GameObjects/Gun.h"
    "./GameObjects/SecurityGuard.h"
    "./GameObjects/SecurityGuard.cpp"
    "./GameObjects/Wall.h"
    "./GameObjects/MuseumItem.h"
    "./GameObjects/HUDOnLoad.h"
)
source_group("Game Objects" FILES ${GameObjects})

set(Player
    "./Player/Player.h"
    "./Player/Player.cpp"
    "./Player/PlayerController.h" 
    "./Player/PlayerController.cpp" 
    "./Player/PlayerControllers.h" 
)
source_group("Player" FILES ${Player})

set(Renderers
)
source_group("Renderers" FILES ${Renderers})

set(Screens
    "./Screens/SplashScreen.h"
    "./Screens/SplashScreen.cpp" 
    "./Screens/MainMenuScreen.h"
    "./Screens/MainMenuScreen.cpp" 
    "./Screens/GameScreen.h"
    "./Screens/GameScreen.cpp" 
    "./Screens/GameOverScreen.h"
    "./Screens/GameOverScreen.cpp" 
    "./Screens/ScreenManager.h"
    "./Screens/ScreenManager.cpp"
)
source_group("Screens" FILES ${Screens})

set(ImGui
    "../Middleware/ImGui/imgui.cpp"
    "../Middleware/ImGui/imgui.h"
    "../Middleware/ImGui/imgui_demo.cpp"
    "../Middleware/ImGui/imgui_draw.cpp"
    "../Middleware/ImGui/imgui_impl_opengl3.cpp"
    "../Middleware/ImGui/imgui_impl_opengl3.h"
    "../Middleware/ImGui/imgui_impl_opengl3_loader.h"
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

set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
    ${GameObjects}
    ${Player}
    ${Renderers}
    ${Screens}
    ${ImGui}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME}  ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE SampleGame)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
)

################################################################################
# Compile definitions
################################################################################
if(MSVC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "UNICODE"
        "WIN32_LEAN_AND_MEAN"
        "_WINSOCKAPI_"   
        "_WINSOCK_DEPRECATED_NO_WARNINGS"
        "NOMINMAX"
        "_CRT_SECURE_NO_WARNINGS;"
    )
endif()

target_precompile_headers(${PROJECT_NAME} PRIVATE
    <vector>
    <map>
    <stack>
    <string>
    <list>
    <thread>
     <atomic>
    <functional>
    <iostream>
    <set>
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            /Oi;
            /Gy
        >
        /permissive-;
        /std:c++latest;
        /sdl;
        /W3;
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Y-
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            /OPT:REF;
            /OPT:ICF
        >
    )
else() #this was for ps4 specifically
	target_compile_options(${PROJECT_NAME} PRIVATE
        #-frtti;
        -fexceptions;
        -std=c++17;
        #${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        #${DEFAULT_CXX_EXCEPTION_HANDLING};
    )
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../Middleware/ReactPhysics3D/ORBIS/include")
endif()

################################################################################
# Dependencies
################################################################################
if(MSVC)
    target_link_libraries(${PROJECT_NAME} LINK_PUBLIC  "Winmm.lib")
    target_link_libraries(${PROJECT_NAME} LINK_PUBLIC  "xinput.lib")
endif()

include_directories(".")
include_directories("./GameObjects")
include_directories("./Renderers")
include_directories("./Screens")
include_directories("./Player")
include_directories("../GameEngine/")
include_directories("../GameEngine/Maths/")
include_directories("../GameEngine/EntityComponents/")
include_directories("../GameEngine/Scene/")
include_directories("../GameEngine/Scene/Terrain")
include_directories("../GameEngine/WindowingAndInput/")
include_directories("../GameEngine/WindowingAndInput/Win32/")
include_directories("../GameEngine/WindowingAndInput/PS4/")
include_directories("../GameEngine/Physics/")
include_directories("../GameEngine/Physics/CollisionDetection/")
include_directories("../GameEngine/Graphics/Renderer/")
include_directories("../GameEngine/Graphics/Renderer/RenderingSupport/")
include_directories("../GameEngine/Graphics/Camera/")
include_directories("../GameEngine/Graphics/Lights/")
include_directories("../GameEngine/Graphics/UI/")
include_directories("../GameEngine/Debugging/")
include_directories("../GameEngine/AssetsHandling/")
include_directories("../GameEngine/AI/BehaviorTrees/")
include_directories("../GameEngine/AI/PathFinding/")
include_directories("../GameEngine/AI/PushdownAutomata/")
include_directories("../GameEngine/AI/StateMachine/")
include_directories("../Middleware/ImGui/")

################################################################################
# Link appropriate project libs
################################################################################
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC GameEngine)

if(GRAPHICS_API STREQUAL "VULKAN")
    include_directories("../VulkanRendering/")
    target_link_libraries(${PROJECT_NAME} LINK_PUBLIC VulkanRendering)
elseif(GRAPHICS_API STREQUAL "OpenGL")
    include_directories("../OpenGLRendering/")
    target_link_libraries(${PROJECT_NAME} LINK_PUBLIC OpenGLRendering)
endif()

if(BUILD_NETWORKING)
    include_directories("../Networking/")
    target_link_libraries(${PROJECT_NAME} LINK_PUBLIC Networking)
endif()