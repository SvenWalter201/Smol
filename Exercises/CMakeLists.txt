cmake_minimum_required (VERSION 3.8)

add_executable (Exercises "Main.cpp" "FileManagement/FileManager.cpp" "Level/Level.cpp" "Level/Cell.cpp" "Utility/Log.cpp" "Player/Player.cpp" "source/game/Game.cpp" "source/input/Input.cpp" "source/Graphics/Draw.cpp" "source/Graphics/Renderer.cpp" "source/Graphics/VertexBuffer.cpp" "source/Graphics/IndexBuffer.h" "source/Graphics/IndexBuffer.cpp" "source/Graphics/VertexArray.cpp" "source/Graphics/Shader.cpp" "source/Graphics/Texture.cpp" "source/vendor/stb_image.cpp" "source/game/QuadRenderer.cpp" "source/game/GameObject.cpp" "source/game/Component.cpp" "source/vendor/imgui/imgui_impl_opengl3.cpp" "source/vendor/imgui/imgui_impl_glfw.cpp" "source/vendor/imgui/imgui.cpp" "source/vendor/imgui/imgui_demo.cpp" "source/vendor/imgui/imgui_draw.cpp" "source/vendor/imgui/imgui_tables.cpp" "source/vendor/imgui/imgui_widgets.cpp" "source/Graphics/Material.h" "source/Graphics/Material.cpp" "source/game/Player.h" "source/game/Player.cpp")

add_compile_definitions(GLEW_STATIC) #probably not nessecary

include_directories ("../Libraries/glew-2.1.0/include/")
include_directories ("../Libraries/glfw-3.3.8/include/")
include_directories ("../Libraries/glm/glm/")
include_directories ("source/vendor/imgui/")

target_link_directories(Exercises PUBLIC "../out/build/x86-Debug/Libraries/")
target_link_directories(Exercises PUBLIC "../out/build/x86-Debug/Libraries/glfw-3.3.8/src/")
target_link_directories(Exercises PUBLIC "../out/build/x86-Debug/Libraries/glew-2.1.0/")

target_link_libraries(Exercises glfw3)
target_link_libraries(Exercises glew_s)
target_link_libraries(Exercises opengl32)


