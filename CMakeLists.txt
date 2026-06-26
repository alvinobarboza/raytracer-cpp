cmake_minimum_required(VERSION 4.2)
project(raytracer-cpp)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)

function(include_dependency libName gitUrl gitTag)
    FetchContent_Declare(
            ${libName}
            GIT_REPOSITORY ${gitUrl}
            GIT_TAG    ${gitTag}
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(${libName})
endfunction()

set(LIB1 raylib)
find_package(${LIB1} QUIET)
if (NOT ${LIB1}_FOUND)
    include_dependency(${LIB1} https://github.com/raysan5/raylib.git 6.0)
endif()

add_executable(${PROJECT_NAME} src/main.cpp
        src/Canvas.cpp
        include/Canvas.h
        include/Vec.h
        src/Vec.cpp
        include/Matrix.h
        include/Maths.h
        include/Lights.h
        src/Camera.cpp
        include/Camera.h
        include/Sphere.h
        src/RayTracer.cpp
        include/RayTracer.h
        src/Sphere.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB1})