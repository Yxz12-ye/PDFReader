cmake_minimum_required(VERSION 3.12.0)
project(PDFREADER VERSION 0.1.0 LANGUAGES C CXX)

set(POPPLER_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/poppler-qt6)
set(POPPLER_INCLUDE_DIR ${POPPLER_ROOT_DIR}/include)
set(POPPLER_LIB_DIR ${POPPLER_ROOT_DIR}/lib)
set(POPPLER_BIN_DIR ${POPPLER_ROOT_DIR}/bin)
set(HUSKARUI_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/HuskarUI)
set(HUSKARUI_INCLUDE_DIR ${HUSKARUI_ROOT_DIR}/include)
set(HUSKARUI_LIB_DIR ${HUSKARUI_ROOT_DIR}/lib)
set(HUSKARUI_BIN_DIR ${HUSKARUI_ROOT_DIR}/bin)

file(GLOB SRC   ${CMAKE_CURRENT_SOURCE_DIR}/src/core/*.cpp 
                ${CMAKE_CURRENT_SOURCE_DIR}/src/core/*.h 
                ${CMAKE_CURRENT_SOURCE_DIR}/src/core/*.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/delegates/*.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/delegates/*.h
                ${CMAKE_CURRENT_SOURCE_DIR}/src/delegates/*.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/delegates/model/*.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/delegates/model/*.h
                ${CMAKE_CURRENT_SOURCE_DIR}/src/delegates/model/*.hpp
                )

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

qt_add_executable(PDFREADER ${SRC} ${PROJECT_SRC})

target_compile_definitions(${PROJECT_NAME} PRIVATE NDEBUG)

target_include_directories(PDFREADER PRIVATE ${POPPLER_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE ${POPPLER_LIB_DIR}/poppler-qt6.lib Qt6::Core Qt6::Widgets Qt6::Gui)

set_target_properties(PDFREADER PROPERTIES AUTOMOC ON)

if(WIN32)
    # 使用 add_custom_command 在构建 my_app 后执行复制操作
    add_custom_command(TARGET PDFREADER POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${POPPLER_BIN_DIR}/poppler-qt6.dll" # 源 DLL 路径
        "$<TARGET_FILE_DIR:PDFREADER>"          # 目标目录（my_app 的构建目录）
        COMMENT "复制 MyLibrary.dll 到构建目录"
    )
    # 如果有其他 DLL 依赖，也需要类似地复制。
endif()