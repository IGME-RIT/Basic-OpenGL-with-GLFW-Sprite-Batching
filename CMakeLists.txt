
if(WIN32)
cmake_minimum_required (VERSION 3.6)
else()
cmake_minimum_required (VERSION 3.0)
endif()

project(opengl-sprite-batching)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set (${PROJECT_NAME}._VERSION_MAJOR 1)
set (${PROJECT_NAME}._VERSION_MINOR 0)
set (${PROJECT_NAME}._VERSION_BUILD 0)

	
file(GLOB SOURCE_FILES "source/*.cpp")
file(GLOB HEADER_FILES "header/*.h")
file(GLOB SHADER_FILES "shaders/*.glsl")

source_group("source" FILES ${SOURCE_FILES})
source_group("header" FILES ${HEADER_FILES})
source_group("shaders" FILES ${SHADER_FILES})

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} ${SHADER_FILES})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

if (MSVC)
	#unzip dependencies into build directory
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E tar xfz ${CMAKE_SOURCE_DIR}/lib/glew-1.13.0-win32.zip
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E tar xfz ${CMAKE_SOURCE_DIR}/lib/glfw-3.1.2.bin.WIN32.zip
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E tar xfz ${CMAKE_SOURCE_DIR}/lib/glm-0.9.7.1.zip
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E tar xfz ${CMAKE_SOURCE_DIR}/lib/FreeImage3170Win32Win64.zip
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
	
	#link with dependencies
    target_link_libraries(${PROJECT_NAME}
      ${CMAKE_BINARY_DIR}/glew-1.13.0/lib/Release/Win32/glew32.lib
      ${CMAKE_BINARY_DIR}/glfw-3.1.2.bin.WIN32/lib-vc2015/glfw3.lib
      ${CMAKE_BINARY_DIR}/FreeImage/Dist/x32/FreeImage.lib
      opengl32.lib
    )
	
    include_directories(
        ${CMAKE_BINARY_DIR}/glew-1.13.0/include
        ${CMAKE_BINARY_DIR}/glfw-3.1.2.bin.WIN32/include
        ${CMAKE_BINARY_DIR}/glm
        ${CMAKE_BINARY_DIR}/FreeImage/Dist/x32
    )
	
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD        # Adds a post-build event to MyTest
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
            "${CMAKE_BINARY_DIR}/glew-1.13.0/bin/Release/Win32/glew32.dll"      # <--this is in-file
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)


    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD        # Adds a post-build event to MyTest
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
            "${CMAKE_BINARY_DIR}/FreeImage/Dist/x32/FreeImage.dll"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif (MSVC)
# vim: ts=4 sw=4 et
