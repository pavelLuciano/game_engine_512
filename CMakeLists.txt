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

# Añadir fuentes específicas de ImPlot
list(APPEND SOURCES
    "${IMPLOT_DIR}/implot.cpp"
    "${IMPLOT_DIR}/implot_items.cpp"
    "${IMPLOT_DIR}/implot_demo.cpp"
)

# Añadir otras fuentes
list(APPEND SOURCES
    "${LOGL_DIR}/Camera.cpp"
    "${LOGL_DIR}/Mesh.cpp"
    "${LOGL_DIR}/Model.cpp"
)

# Definir el ejecutable
add_executable(MyApp ${SOURCES})

# Configurar las librerías dependiendo del sistema operativo
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Compilando en Linux")

    # Librerías en Linux
    find_package(OpenGL REQUIRED)
    find_package(Threads REQUIRED)

    target_link_libraries(MyApp
        ${CMAKE_THREAD_LIBS_INIT}
        ${OPENGL_LIBRARIES}
        glfw
        GLEW
        assimp
    )

elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Compilando en Windows (MSYS2 UCRT64)")

    # Ajustar el compilador para MSYS2 UCRT64
    set(CMAKE_C_COMPILER "C:/msys64/ucrt64/bin/gcc.exe")
    set(CMAKE_CXX_COMPILER "C:/msys64/ucrt64/bin/g++.exe")

    # Incluir los directorios de las librerías
    include_directories("C:/msys64/ucrt64/include")
    link_directories("C:/msys64/ucrt64/lib")

    # Librerías en Windows
    find_package(OpenGL REQUIRED)

    target_link_libraries(MyApp
        ${CMAKE_THREAD_LIBS_INIT}
        ${OPENGL_LIBRARIES}
        glfw3
        glew32
        opengl32
        assimp
    )
endif()
