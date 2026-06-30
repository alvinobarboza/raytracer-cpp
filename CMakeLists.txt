cmake_minimum_required(VERSION 4.2)
project(raytracer-cpp)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
        include/Camera.h
        include/Canvas.h
        include/Lights.h
        include/Maths.h
        include/Matrix.h
        include/RayTracer.h
        include/Sphere.h
        include/ThreadPool.h
        include/Utils.h
        include/Vec.h
        src/Camera.cpp
        src/Canvas.cpp
        src/Maths.cpp
        src/RayTracer.cpp
        src/Sphere.cpp
        src/ThreadPool.cpp
        src/Utils.cpp
        src/Vec.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB1})