cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(MyApp)

# Establecer el estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Directorios
set(SRC_DIR         "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR     "${CMAKE_SOURCE_DIR}/include")
set(DEPS_DIR        "${CMAKE_SOURCE_DIR}/dependencies")
set(GLM_DIR         "${DEPS_DIR}/glm")
set(IMGUI_DIR       "${DEPS_DIR}/imgui")
set(IMPLOT_DIR      "${DEPS_DIR}/implot")
set(LOGL_DIR        "${DEPS_DIR}/learn_open_gl")

# Incluir los directorios de cabeceras
include_directories(${INCLUDE_DIR})
include_directories(${DEPS_DIR})
include_directories(${IMGUI_DIR})
include_directories(${IMPLOT_DIR})

# Buscar los archivos fuente en src/
file(GLOB SOURCES "${SRC_DIR}/*.cpp")

# Añadir fuentes específicas de ImGui
list(APPEND SOURCES
    "${IMGUI_DIR}/imgui.cpp"
    "${IMGUI_DIR}/imgui_demo.cpp"
    "${IMGUI_DIR}/imgui_draw.cpp"
    "${IMGUI_DIR}/imgui_tables.cpp"
    "${IMGUI_DIR}/imgui_widgets.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_glfw.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
)
#añadir fuentes especificas de ImPlot
list(APPEND SOURCES
    "${IMPLOT_DIR}/implot.cpp"
    "${IMPLOT_DIR}/implot_items.cpp"
    "${IMPLOT_DIR}/implot_demo.cpp"
)
#otra forma mas rapida de hacerlo
list(APPEND SOURCES
    "${LOGL_DIR/Camera.cpp}"
    "${LOGL_DIR/Mesh.cpp}"
    "${LOGL_DIR/Model.cpp}"
)

# Definir el ejecutable
add_executable(MyApp ${SOURCES})

# Librerías y banderas
find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)

target_link_libraries(MyApp
    ${CMAKE_THREAD_LIBS_INIT}
    ${OPENGL_LIBRARIES}
    glfw
    GLEW
    assimp
)
