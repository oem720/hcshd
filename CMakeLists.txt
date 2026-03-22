cmake_minimum_required(VERSION 3.23)
project(hcshd)

ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(CMAKE_CXX_STANDARD 20)

set(RUNTIME_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE PATH "Directory for dlls and binaries")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE PATH "Directory for binaries")
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE PATH "Directory for dlls")

IF(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin CACHE PATH "Directory for dlls and binaries")
endif()

set(HCSHD_PROJECT_DIR ${PROJECT_SOURCE_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/CMake)

file(GLOB_RECURSE SOURCE_FILES src/*.hpp src/*.cpp src/*.h src/*.c)

add_executable(hcshd ${SOURCE_FILES})

target_compile_definitions(hcshd PUBLIC _CRT_SECURE_NO_WARNINGS)
target_compile_definitions(hcshd PUBLIC NOMINMAX)
target_compile_definitions(hcshd PUBLIC HCSHD_PROJECT_DIR="${HCSHD_PROJECT_DIR}")

target_include_directories(hcshd PUBLIC src)

if(CMAKE_GENERATOR MATCHES "Visual Studio")
	foreach(_source IN ITEMS ${SOURCE_FILES})
		if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
        else()
            set(_source_rel "${_source}")
        endif()
        get_filename_component(_source_path "${_source_rel}" PATH)
		string(REPLACE "src" "" _source_path_msvc "${_source_path}")
		string(REPLACE "ShaderCompiler" "" _source_path_msvc "${_source_path_msvc}")
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path_msvc}")
        source_group("${_source_path_msvc}" FILES "${_source}")
	endforeach()
endif()

if(WIN32)
	target_include_directories(hcshd PUBLIC $ENV{VULKAN_SDK}/Include/)
	target_link_directories(hcshd PUBLIC $ENV{VULKAN_SDK}/Lib/)
	target_link_libraries(hcshd PUBLIC vulkan-1.lib;comctl32.lib;propsys.lib;shlwapi.lib)
	
	target_link_libraries(hcshd PUBLIC slang.lib)
	target_link_libraries(hcshd PUBLIC
		$<$<CONFIG:Debug>:shaderc_combinedd.lib>
		$<$<CONFIG:Debug>:dxcompilerd.lib>
		$<$<CONFIG:Debug>:spirv-cross-cored.lib>
		$<$<CONFIG:Debug>:spirv-cross-reflectd.lib>
		$<$<CONFIG:Debug>:SPIRV-Tools-optd.lib>
		
		$<$<CONFIG:Release>:shaderc_combined.lib>
		$<$<CONFIG:Release>:dxcompiler.lib>
		$<$<CONFIG:Release>:spirv-cross-core.lib>
		$<$<CONFIG:Release>:spirv-cross-reflect.lib>
		$<$<CONFIG:Release>:SPIRV-Tools-opt.lib>
	)
else()
	message(FATAL_ERROR "ERROR: Linux and Mac not yet supported! Fix me or pester Owen!")
endif()