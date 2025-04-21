cmake_minimum_required(VERSION 3.10.0)

project(demo VERSION 0.1.0 LANGUAGES C CXX)

include(FetchContent)

# Eigen
FetchContent_Declare(
    Eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG 3.4.0
)

# fmt
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 10.2.1
)

# yalantinglibs
FetchContent_Declare(
    yalantinglibs
    GIT_REPOSITORY https://github.com/alibaba/yalantinglibs.git
    GIT_TAG 0.4.0
)

set(HELLOIMGUI_DOWNLOAD_FREETYPE_IF_NEEDED ON)
FetchContent_Declare(
    hello-imgui
    GIT_REPOSITORY https://github.com/pthom/hello_imgui.git
    GIT_TAG master
)

FetchContent_MakeAvailable(Eigen fmt yalantinglibs hello-imgui)

set(CMAKE_CXX_STANDARD 20)  # yalantinglibs需要C++20
set(CMAKE_CXX_STANDARD_REQUIRED ON)

hello_imgui_add_app(demo main.cpp)
target_link_libraries(demo PRIVATE 
    Eigen3::Eigen 
    fmt::fmt
    yalantinglibs::yalantinglibs
)

