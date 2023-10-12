# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("Exercises")

# Include sub-projects.
add_subdirectory ("Exercises")
add_subdirectory ("Libraries/glfw-3.3.8")
add_subdirectory ("Libraries/glew-2.1.0/build/cmake")
add_subdirectory ("Libraries/glm")
