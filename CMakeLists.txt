cmake_minimum_required(VERSION 3.23)
project(ImGuiBaseDX9)

set(CMAKE_CXX_STANDARD 20)


file(GLOB IMGUI
        ${PROJECT_SOURCE_DIR}/external/imgui/*.cpp
        ${PROJECT_SOURCE_DIR}/external/imgui/*.h
        )

file(GLOB MINHOOK
        ${PROJECT_SOURCE_DIR}/external/minhook/*.c
        ${PROJECT_SOURCE_DIR}/external/minhook/*.h
        ${PROJECT_SOURCE_DIR}/external/minhook/hde/*.c
        ${PROJECT_SOURCE_DIR}/external/minhook/hde/*.h
        )

file(GLOB SRC_FILES
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*.h
        ${PROJECT_SOURCE_DIR}/src/gui/*.cpp
        ${PROJECT_SOURCE_DIR}/src/gui/*.h
        ${PROJECT_SOURCE_DIR}/src/hooks/*.cpp
        ${PROJECT_SOURCE_DIR}/src/hooks/*.h
        ${PROJECT_SOURCE_DIR}/src/style/*.cpp
        ${PROJECT_SOURCE_DIR}/src/style/*.h)


add_library(ImGuiBaseDX9 SHARED ${SRC_FILES} ${IMGUI} ${MINHOOK})
