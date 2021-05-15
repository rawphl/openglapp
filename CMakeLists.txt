cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# specify name of the project and specify which language to compile for
project(opengl-template LANGUAGES CXX)

set(CPM_DOWNLOAD_VERSION 0.32.0)

if(CPM_SOURCE_CACHE)
    set(CPM_DOWNLOAD_LOCATION "${CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
elseif(DEFINED ENV{CPM_SOURCE_CACHE})
    set(CPM_DOWNLOAD_LOCATION "$ENV{CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
else()
    set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
endif()

if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
    message(STATUS "Downloading CPM.cmake to ${CPM_DOWNLOAD_LOCATION}")
    file(DOWNLOAD
            https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
            ${CPM_DOWNLOAD_LOCATION}
            )
endif()

include(${CPM_DOWNLOAD_LOCATION})
#-----------------------------------------------------------------------------#
# define the asset path in c++
set(ASSETS_DIR ${PROJECT_SOURCE_DIR}/src/assets)
add_compile_definitions(ASSETS_PATH="${ASSETS_DIR}")

#-----------------------------------------------------------------------------#
# list of all source files
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS "${SRC_DIR}/*.h")
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE SHADER_FILES CONFIGURE_DEPENDS "${ASSETS_DIR}/shaders/*.glsl")

# GLAD
CPMAddPackage(
        NAME glad
        GITHUB_REPOSITORY Dav1dde/glad
        VERSION 0.1.33
)

# GLM
CPMAddPackage(
        NAME glm
        GITHUB_REPOSITORY g-truc/glm
        GIT_TAG 0.9.9.7
)

# GLFW
CPMAddPackage(
        NAME glfw
        GITHUB_REPOSITORY glfw/glfw
        GIT_TAG 3.3.2
        OPTIONS
        "GLFW_BUILD_TESTS Off"
        "GLFW_BUILD_EXAMPLES Off"
        "GLFW_BUILD_DOCS Off"
        "GLFW_INSTALL Off"
        "GLFW_USE_HYBRID_HPG On"
)

# assimp
CPMAddPackage(
        NAME assimp
        GITHUB_REPOSITORY assimp/assimp
        VERSION 5.0.1
        OPTIONS
        "BUILD_ASSIMP_TOOLS On"
        "ASSIMP_BUILD_STATIC_LIB ON"
)

# stb
CPMAddPackage(
        NAME stb
        GITHUB_REPOSITORY nothings/stb
        GIT_TAG master
)

# bullet
CPMAddPackage(
        NAME bullet
        GITHUB_REPOSITORY bulletphysics/bullet3
        GIT_TAG master
)

# put all external targets into a seperate folder to not pollute the project folder
set_target_properties(glad glad-generate-files glfw PROPERTIES FOLDER ExternalTargets)

# Source file grouping of visual studio and xcode
CPMAddPackage(
        NAME GroupSourcesByFolder.cmake
        GITHUB_REPOSITORY TheLartians/GroupSourcesByFolder.cmake
        VERSION 1.0
)

#-----------------------------------------------------------------------------#
# list all files that will either be used for compilation or that should show
# up in the ide of your choice
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} ${SHADER_FILES})
GroupSourcesByFolder(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC src)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 11) # use c++11

# specify libraries to link with after compilation
target_link_libraries(${PROJECT_NAME} PRIVATE glad glfw glm)