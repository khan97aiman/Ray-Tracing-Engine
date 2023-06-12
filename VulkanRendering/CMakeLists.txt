set(PROJECT_NAME VulkanRendering)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "Precompiled.h"
    "VulkanUtils.h"
    "VulkanBuffers.h"
    "VulkanBVHBuilder.h"
    "VulkanCompute.h"
    "VulkanComputePipelineBuilder.h"
    "VulkanDescriptorSetLayoutBuilder.h"
    "VulkanDynamicRenderBuilder.h"
    "VulkanMesh.h"
    "VulkanPipeline.h"
    "VulkanPipelineBuilder.h"
    "VulkanRenderer.h"
    "VulkanRenderPassBuilder.h"
    "VulkanRTShader.h"
    "VulkanShader.h"
    "VulkanShaderBuilder.h"
    "VulkanTexture.h"
    "SmartTypes.h"
    "VulkanAssetLoader.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "Precompiled.cpp"
    "VulkanUtils.cpp"
    "VulkanBuffers.cpp"
    "VulkanBVHBuilder.cpp"
    "VulkanCompute.cpp"
    "VulkanComputePipelineBuilder.cpp"
    "VulkanDescriptorSetLayoutBuilder.cpp"
    "VulkanDynamicRenderBuilder.cpp"
    "VulkanMesh.cpp"
    "VulkanPipelineBuilder.cpp"
    "VulkanRenderer.cpp"
    "VulkanRenderPassBuilder.cpp"
    "VulkanRTShader.cpp"
    "VulkanShader.cpp"
    "VulkanShaderBuilder.cpp"
    "VulkanTexture.cpp"
    "VulkanAssetLoader.cpp"
)
source_group("Source Files" FILES ${Source_Files})

################################################################################
# Shader and Textures setup
################################################################################
# Shaders
file(GLOB SHADER_FILES 
    ${ASSET_ROOT}Shaders/VK/*.vert
    ${ASSET_ROOT}Shaders/VK/*.frag
    ${ASSET_ROOT}Shaders/VK/*.comp
    ${ASSET_ROOT}Shaders/VK/*.geom
    ${ASSET_ROOT}Shaders/VK/*.tesc
    ${ASSET_ROOT}Shaders/VK/*.tese
    ${ASSET_ROOT}Shaders/VK/*.rgen
    ${ASSET_ROOT}Shaders/VK/*.rint
    ${ASSET_ROOT}Shaders/VK/*.rahit
    ${ASSET_ROOT}Shaders/VK/*.rchit
    ${ASSET_ROOT}Shaders/VK/*.rmiss
    ${ASSET_ROOT}Shaders/VK/*.rcall
    ${ASSET_ROOT}Shaders/VK/*.task
    ${ASSET_ROOT}Shaders/VK/*.mesh
    ${ASSET_ROOT}Shaders/VK/*.glslh
)
source_group("Shader Files" FILES ${SHADER_FILES})
set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
    ${SHADER_FILES}
)

foreach (file ${SHADER_FILES})
    get_filename_component(file_name ${file} NAME)
	get_filename_component(file_ext ${file} EXT)
	
	if(file_ext STREQUAL ".h" OR file_ext STREQUAL ".cpp")
		continue()
	endif()
		
	if( file_ext STREQUAL  ".vert" OR
		file_ext STREQUAL  ".frag" OR
		file_ext STREQUAL  ".comp" OR
		file_ext STREQUAL  ".geom" OR
		file_ext STREQUAL  ".tesc" OR
		file_ext STREQUAL  ".tese" OR
		file_ext STREQUAL  ".rgen" OR
		file_ext STREQUAL  ".rint" OR
		file_ext STREQUAL  ".rahit" OR
		file_ext STREQUAL  ".rchit" OR
		file_ext STREQUAL  ".rmiss" OR
		file_ext STREQUAL  ".rcall" OR
		file_ext STREQUAL  ".task" OR
		file_ext STREQUAL  ".mesh"
	)
		message("Adding custom command to ${file}")
		get_filename_component(file_dir ${file} ABSOLUTE)
        set(SPIRV_OUTPUT ${file_name}.spv)
		set(SPIRV_ABS_INPUT ${file_dir})
		set(SPIRV_ABS_OUTPUT ${file_dir}.spv)
		
		add_custom_command(
			OUTPUT ${SPIRV_ABS_OUTPUT}
			
			COMMENT "Compiling GLSL shader:"
			COMMAND ${Vulkan_GLSLANG_VALIDATOR_EXECUTABLE} -V  ${SPIRV_ABS_INPUT} -o ${SPIRV_ABS_OUTPUT}
            DEPENDS ${file}
			VERBATIM
		)
        list(APPEND SPIRV_BINARY_FILES ${SPIRV_OUTPUT})   
	endif()
endforeach()

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/Precompiled.h>"
)

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE VulkanRendering)

set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
)
################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
    $<$<CONFIG:Debug>:
        MultiThreadedDebugDLL
    >
    $<$<NOT:$<OR:$<CONFIG:Debug>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
)
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Debug>:"
        "VK_PROTOTYPES"
    ">"
    "NOMINMAX;"
    "_MBCS"
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

target_include_directories (${PROJECT_NAME} 
    PUBLIC ${VULKAN_INCLUDE_DIRS}
)	

target_include_directories (${PROJECT_NAME} 
    PUBLIC ${Vulkan_INCLUDE_DIR}
)	

################################################################################
# Dependencies
################################################################################
set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "$<$<CONFIG:Debug>:"
    ">"
    "GameEngine"
)

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

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")
target_link_libraries(${PROJECT_NAME} PRIVATE ${Vulkan_LIBRARIES})

#if(MSVC)
#target_link_libraries(${PROJECT_NAME} PRIVATE "$ENV{VULKAN_SDK}/lib/VkLayer_utils.lib")
#endif()

add_custom_target(
    SHADER_FILES
    DEPENDS ON ${SPIRV_BINARY_FILES}
)
add_dependencies(${PROJECT_NAME} SHADER_FILES)