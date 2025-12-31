cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(GLFW_test)

# Find required packages
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# Collect source files
set(PROJECT_SOURCES glad.c gl_lession.cpp Shader/Shader.cpp)
set(PROJECT_SHADERS 
    vertexShader.glsl 
    fragmentShader.glsl 
    fragShader.glsl
)

# Create executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Link libraries using modern approach
target_link_libraries(${PROJECT_NAME} 
    glfw 
    ${CMAKE_DL_LIBS}
    OpenGL::GL
)

# Copy shader files to build directory so the executable can find them
foreach(shader ${PROJECT_SHADERS})
    configure_file(${shader} ${shader} COPYONLY)
endforeach()

# Set C++14 standard explicitly
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)