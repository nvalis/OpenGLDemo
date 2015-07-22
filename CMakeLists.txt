# CMake entry point.
# Note that this CMakeLists.txt in fully independent from the one in the parent directory
# (since that's the goal of this tutorial !)

# For an introduction to CMake, see
# http://www.cmake.org/cmake/help/cmake_tutorial.html (at least steps 1 and 2)

cmake_minimum_required (VERSION 2.6)
project (Demo)

find_package(OpenGL REQUIRED)

add_subdirectory(external)

# Ask the user to give the paths to GLFW, GLEW and GLM.
# On Linux this can be found automatically with pkg-config; 
# see http://stackoverflow.com/questions/6889264/cmake-flags-for-opengl-using-glew-and-glfw, for instance.

# external/glfw-3.0.3/include/GLFW/
#set(GLFW_INCLUDE_PATH "" CACHE PATH "The directory that contains GL/glfw.h")
#set(GLFW_LIBRARY "" CACHE FILEPATH "libglfw.a or glfw.lib")

# external/glew-1.9.0/include/
#set(GLEW_INCLUDE_PATH "" CACHE PATH "The directory that contains GL/glew.h")
#set(GLEW_LIBRARY "" CACHE FILEPATH "libglew.a or glew.lib" )

# external/glm-0.9.4.0/
#set(GLM_INCLUDE_PATH "" CACHE PATH "The directory that contains glm/glm.hpp")

set(GLFW_INCLUDE_PATH external/glfw-3.0.3/include/GLFW/) # dir containing GL/glfw.h
set(GLFW_LIBRARY glfw.lib) # libglfw.a or glfw.lib
set(GLEW_INCLUDE_PATH external/glew-1.9.0/include/) # dir containing GL/glew.h
set(GLEW_LIBRARY glew.lib) # libglew.a or glew.lib

set(HEADER_FILES
	# all .hpp here
	common/shader.hpp
)

set(SOURCE_FILES
	# all .cpp here
	demo.cpp
	common/shader.cpp
)

set(SHADER_FILES
	shader.frag
	shader.vert
)


include_directories(
	${GLFW_INCLUDE_PATH}
	${GLEW_INCLUDE_PATH}
	.
)
add_executable(Demo
	${HEADER_FILES}
	${SOURCE_FILES}
	${SHADER_FILES}
)
target_link_libraries(Demo
	${OPENGL_LIBRARY} # filled by "find_package(OpenGL REQUIRED)"
	#${GLFW_LIBRARY}
	#${GLEW_LIBRARY}
	GLFW_303
	GLEW_190
)

# copy shader files before execution
foreach(SHADER ${SHADER_FILES})
	add_custom_command(
		TARGET Demo POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${SHADER}" "${CMAKE_CURRENT_BINARY_DIR}/"
	)
endforeach()


if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	message("You're on Mac OS!")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	message("You're on Linux!")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	message("You're on Windows!")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") # Yes this is weird but you have to repeat the "if" here.

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)
